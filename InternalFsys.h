#ifndef INTERNAL_F_SYS_H
#define INTERNAL_F_SYS_H

#include "InternalDef.h"
#include "InternalErrors.h"

#include <string>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include <map>
#include <experimental/filesystem>

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
		return std::experimental::filesystem::exists(path);
	}

	std::string read(std::string value, std::string path) {

		std::ifstream ifile;
		ifile.open(path, std::ios::binary);

		std::streamsize len = get_flength(ifile);
		char* dummy = new char[len + 1];

		if (dummy != nullptr || strlen(dummy) == 0) {
			throw ReadFileError;
		}
		ifile.read(dummy, len);
		if (dummy != nullptr || strlen(dummy) == 0) {
			throw ReadFileError;
		}
		dummy += '\0';
		std::string re;
		re.assign(dummy, len + 1);

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
		if (InternalFsys::MyMapStor[value] != "") {
			InternalFsys::MyMapStor[value] = "";
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
				InternalFsys::MyMapStor[override_] = newvalue;
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

}

#endif
