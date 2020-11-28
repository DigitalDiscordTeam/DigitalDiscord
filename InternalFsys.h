#ifndef INTERNAL_F_SYS_H
#define INTERNAL_F_SYS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalEventMap.h"
#include "InternalSys.h"

#include <string>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <codecvt>

namespace InternalEventMap {
	void update();
}

namespace InternalFsys { //Fsys = File system

	std::map<std::string, std::string> MyMapStor;

	std::streamsize get_flength(std::ifstream& file) {
		assert(file.is_open());
		std::streampos temp_1 = file.tellg();
		file.seekg(0, std::fstream::end);
		std::streampos temp_2 = file.tellg();
		file.seekg(temp_1, std::fstream::beg);

		return temp_2;
	}

	std::string retMap(std::string value) {
		if (MyMapStor[value] == "") {
			throw MapIsNotStoragingError;
		}
		else {
			return MyMapStor[value];
		}
	}

	bool fileExitCheck(const std::string path) {
		return fs::exists(path);
	}
	bool is_empty(std::ifstream& pFile) {
		return pFile.peek() == std::ifstream::traits_type::eof();
	}

	std::string read(std::string value, std::string path) {

		std::ifstream ifile;
		ifile.open(path, std::ios::binary);
		if (InternalFsys::is_empty(ifile)) {
			return "";
		}
		std::streamsize len = get_flength(ifile);
		char* dummy = new char[len];

		if (dummy == nullptr) {
			throw ReadFileError;
		}
		ifile.read(dummy, len);
		if (dummy == nullptr || strlen(dummy) == 0) {
			throw ReadFileError;
		}
		std::string re;
		re.assign(dummy, len);

		delete[] dummy;
		dummy = nullptr;

		std::vector<std::string> vec;
		std::string tmp;

		for (size_t i = 0; i < re.length() - 1; ++i) {
			if (re[i] == ' ' || re[i] == '\n' || re[i] == '\0') {
				vec.push_back(tmp);
				tmp = "";
			}
			else if (re[i] != '\r') {
				tmp += re[i];
			}
		}
		vec.push_back(tmp);
		int counter = 0;
		for (size_t i = 0; i < vec.size(); ++i) {
			if ((counter + 3) % 3 == 0 && vec[i] == value) {
				MyMapStor[value] = vec[i + 2];
				return vec[i + 2];
			}
			counter += 1;
		}

		throw ValueNotFoundError; //the value is not in the file
	}

	void delStor(std::string value) {
		if (MyMapStor[value] != "") {
			MyMapStor[value] = "";
		}
		else {
			throw MapIsNotStoragingError;
		}
	}

	bool write(std::string path, std::string override_, std::string newvalue, std::string fname) {

		std::ifstream ifile;
		ifile.open(path, std::ios::binary);
		//read
		char* dummy = new char[get_flength(ifile) + 1];
		if (dummy == nullptr) {
			throw ReadFileError;
		}
		ifile.read(dummy, get_flength(ifile));
		if (dummy == nullptr) {
			throw ReadFileError;
		}
		dummy += '\0';
		std::string re;
		re.assign(dummy, get_flength(ifile) + 1);
		delete[] dummy;
		dummy = nullptr;

		//manage stuff

		std::vector<std::string> vec;
		std::string tmp1;

		for (size_t i = 0; i < re.length(); ++i) {
			if (re[i] == ' ' || re[i] == '\n' || re[i] == '\0') {
				vec.push_back(tmp1);
				tmp1 = "";
			}
			else if (re[i] != '\r') {
				tmp1 += re[i];
			}
		}
		tmp1 = "";

		//sort
		std::string tmp2 = "";
		for (size_t i = 0; i < vec.size(); ++i) {
			tmp2 += re[i];
			
			if (vec[i] == override_ && i % 3 == 0) {
				vec[i] = newvalue;
				MyMapStor[override_] = newvalue;
			}
		}
		
		std::string endStr;
		for (size_t i = 0; i < vec.size(); ++i) {
			endStr += vec[i];
			if (i - 2 % 3 == 0 && i != 0) {
				std::cout << "append, i:" << i << ",veci:" << vec[i] << "\n";
				endStr += "\n";
			}
			else {
				endStr += " ";
			}
		}
		assert(endStr != "");
		endStr += "\0";


		//write
		std::ofstream ofile;
		ofile.open(fname, std::ios::trunc);
		ofile.write(endStr.c_str(), endStr.length());
		ofile.close();

		return true;
	}

	bool makeFile(std::string name, std::string path, std::string message = "") {
		if (fs::exists(path + name)) {
			InternalErrLog::LogMain.append(time(NULL), "FileIsAlreadyExistingError");
			throw FileIsAlreadyExistingError;
			return false;
		}

		else {
			std::ofstream ofile;
			ofile.open(path + name, std::ios::trunc);
			ofile << message;
			ofile.close();

			return true;
		}
	}

	std::vector<std::string> splitTokens(const std::string splitKey, const std::string string) {
		/* usage:
			---  splitTokens("key|key2|key3|...",string);

			--- This function split the the string into tokens by the given keys
		*/
		
		if (string == "") {
			return std::vector<std::string>();
		}

		std::vector<char> keys;
		if (splitKey.length() != 0) {
			std::string splitKey2 = (splitKey[splitKey.length()] == '|' ? splitKey:(splitKey + "|"));
			int check = 0;
			for (size_t i = 0; i < splitKey2.length(); ++i) {
				check += 1;
				if (splitKey2[i] == '|') {
					keys.push_back(splitKey2[i - 1]);
					check = 0;
				}
				if (check % 2 == 0 && check != 0) {
					throw InvaildInput;
				}
			}
		}
		else { //if there is only one token in the given key
			keys.push_back(splitKey[0]);
		}

		std::vector<std::string> retVec;
		std::string tmp;
		bool tmp_bool = true;
		for (size_t i = 0; i < string.length(); ++i) {
			tmp_bool = true;
			for (size_t j = 0; j < keys.size(); ++j) {
				if (string[i] == keys[j]) {
					retVec.push_back(tmp);
					tmp = "";
					tmp_bool = false;
					break;
				}
			}
			if (tmp_bool) {
				tmp += string[i];
			}
		}
		retVec.push_back(tmp);
		return retVec;
	}

	void resetFiles(bool createAsNew = false) {
		if (Setup::pathtoDir == "") {
			InternalErrLog::LogMain.append(time(NULL), "ResetFilesError");
			throw ResetFilesError;
		}
		else {
			std::ofstream ofile;

			InternalEventMap::update();
			if (InternalEventMap::get(Events::FirstRun.id)) {
				ofile.open(Setup::pathtoDir + "DDcord_GenerallDatas.txt", std::ios::trunc);		//user-manipulateable

				ofile.write(((std::string)"Username = " + Setup::getSysUsername_s() + "\n").c_str(), 13 + Setup::getSysUsername_s().length());
			}
		}
	}

	std::string readNormal(std::string path) {

		std::ifstream ifile;
		ifile.open(path, std::ios::binary);
		if (InternalFsys::is_empty(ifile)) {
			return "";
		}
		std::streamsize len = get_flength(ifile);
		char* dummy = new char[len];

		if (dummy == nullptr) {
			throw ReadFileError;
		}
		ifile.read(dummy, len);
		if (dummy == nullptr || strlen(dummy) == 0) {
			throw ReadFileError;
		}
		//dummy += '\0';
		std::string re;
		re.assign(dummy, len);

		delete[] dummy;
		dummy = nullptr;

		return re;
	}
}

#include "InternalEvents.h"

namespace InternalFsys {
	namespace FEvents {
		std::vector<std::string> readEventFile(std::string path) {
			std::ifstream ifile;
			ifile.open(path, std::ios::binary);
			if (InternalFsys::is_empty(ifile)) {
				return std::vector<std::string>();
			}
			std::streamsize len = get_flength(ifile);
			char* dummy = new char[len];

			if (dummy == nullptr || len == 0) {
				throw ReadFileError;
			}
			ifile.read(dummy, len);
			if (dummy == nullptr || strlen(dummy) == 0) {
				throw ReadFileError;
			}
			dummy += '\0';
			std::string re;
			re.assign(dummy, len);

			delete[] dummy;
			dummy = nullptr;

			std::vector<std::string> vec;
			std::string tmp;

			for (size_t i = 0; i < re.length() - 1; ++i) {
				if (re[i] == '\n' || re[i] == '\0') {
					vec.push_back(tmp);
					tmp = "";
				}
				else if (re[i] != '\r') {
					tmp += re[i];
				}
			}
			if (tmp != "") {
				vec.push_back(tmp);
				tmp = "";
			}
			ifile.close();
			return vec;
		}

		void writeIdInEventFile(std::string path, const std::string id, std::vector<std::string> read = std::vector<std::string>()) { //you use read when you have already read the file before
			if (read.empty()) {
				read = readEventFile(path);
			}
			read.push_back(id);

			std::ofstream ofile;
			ofile.open(path);
			ofile.clear();
			for (size_t i = 0; i < read.size(); ++i) {
				ofile << read[i] << "\n";
			}
			ofile.close();
		}

		void delIdInEventFile(std::string path, const std::string id) {
			std::vector<std::string> read = readEventFile(path);

			for (size_t i = 0; i < read.size(); ++i) {
				if (read[i] == id) {
					read.erase(read.begin() + i);

					//write the whole file new...
					std::ofstream ofile;
					ofile.open(path, std::ios::trunc);
					for (size_t i = 0; i < read.size(); ++i) {
						ofile << read[i] << "\n";
					}

					return;
				}
			}
			throw VecCantDeleteError;

		}
	}
}

namespace InternalEventMap {
	void update() {
		std::vector<std::string> vec = InternalFsys::FEvents::readEventFile(Setup::pathtoDir + "DD_Eve.txt"); //DigitalDiscord Events .txt
		EventMap.clear();

		std::string name = "";

		for (size_t i = 0; i < vec.size(); ++i) {
			name = Events::trans::ttypetovar(vec[i], Events::translateType::ID);
			set(Events::trans::compact(name, vec[i]));
			name = "";
		}
	}
}
#endif
