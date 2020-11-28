#ifndef COMMAND_FILE_H
#define COMMAND_FILE_H

#include "InternalDef.h"
#include "InternalFsys.h"
#include "InternalSys.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalFileVec.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using tokenType = std::vector<std::string>;

#define isEght(tokens) if(((tokenType)tokens).size() < 2) {return false;}

class CommandFile {
private:
	std::string filename;
	std::string path;
	std::ifstream file;
	tokenType read;

	bool comInfo(tokenType tokens) {
		std::string tpath;
		if (tokens.size() < 2) { //no arguments
			std::cout << "---info---\nnone: 0\n";
		}
		else  {
			tpath = tokens[1];
			if (tpath == "std") {
				tpath = Setup::pathtoDir + "DDcord_eve.txt";
			}
			tokenType tmpTokens = InternalFsys::FEvents::readEventFile(tpath);
			for (size_t i = 0; i < tmpTokens.size(); ++i) {
				if (InternalEventVec::isIn(tmpTokens[i])) {
					std::cout << "Event:" << InternalEventVec::eventVec[InternalEventVec::getIndex(tmpTokens[i])].name << "\n";
				}
			}
		}

		return true; //this command always success because it need no arguments
	}

	bool comCat(tokenType tokens) {
		isEght(tokens);
		bool asFvar = false;
		bool trunc = false;
		std::string varkey = "";
		for (size_t i = 1; i < read.size(); ++i) {
			if (read[i][0] == '-') { //command
				if (read[i] == "-as") {
					if (read.size() < i+1) { //too few arguments
						return "";
					}
					else if ((read[i+1] == "fvar" || read[i+1] == "findvariable") && (read[i+2][0] != '-' || read[i+2][0] != '*')) {
						asFvar = true;
						varkey = read[i + 2];
						i += 2;
					}
					else if (read[i + 1] == "fval" || read[i+1] == "findvariable") {
						return "";
					}
					else {
						return "";
					}
				}
				else if (read[i] == "-del") {
					trunc = true;
				}
			}
			else if (read[i][0] == '*') { //filename
				read[i].erase(read[i].begin()); //remove the *

				assert(Setup::dirPathExits);

				if (asFvar) {
					if (trunc) {
						std::string ret = InternalFsys::read(varkey, Setup::pathtoDir + read[i]);
						std::ofstream ofile;
						ofile.open(read[i], std::ios::trunc);
						ofile.close();
						std::cout << ret;
						return true;
					}
					else {
						std::cout << InternalFsys::read(varkey,Setup::pathtoDir + read[i]);
						return true;
					}
				}
				if (trunc) {
					std::string ret = InternalFsys::readNormal(Setup::pathtoDir + read[i]);
					std::ofstream ofile;
					ofile.open(Setup::pathtoDir + read[i], std::ios::trunc);
					ofile.close();
					std::cout << ret;
					return true;
				}
				std::cout << InternalFsys::read(varkey, Setup::pathtoDir + read[i]);
				return true;
			}
		}
		return false; //no filename given
	}

	bool comCorr(tokenType tokens) { //corrupted line
		isEght(tokens);
		bool bn = false;
		
		if (read.size() >= 3) { //bool is given
			if (read[2] == "-true" || read[2] == "-t") {
				bn = true;
			}
		}
		int length = std::stoi(read[1]);
		InternalPCO::corruptedLine(length);
		if (bn) { std::cout << "\n"; }
		return true;
	}
	
	bool comCout(tokenType tokens) {
		isEght(tokens);
		bool bn = false;
		bool br = false;
		for (size_t i = 1; i < read.size(); ++i) { //read[0] = command
			if (read[i][0] == '-') {
				if (read[i] == "-bn") {
					bn = !bn;
				}
				if (read[i] == "-r") {
					br = !br;
				}
			}
			if (read[i][0] == '*') { //text to print
				read[i].erase(read[i].begin());
				std::string print;
				for (size_t j = i; j < read.size(); ++j) {
					print += read[j] + " ";
				}
				if (br) { std::cout << "\r"; }
				std::cout << print;
				if (bn) { std::cout << "\n"; }
				return true;
			}
		}
		return false;
	}

	bool comSer(tokenType tokens) {
		isEght(tokens);
		bool wpath = false;
		bool wsize = false;
		std::string searchName = "";
		
		size_t sizeSearchFrom = 0;
		size_t sizeSearchTo = 0;
		for (size_t i = 1; i < tokens.size(); ++i) {
			//std::cout << "token:" << tokens[i] << "|i:" << i << "\n";
			if (tokens[i][0] == '-') {
				if (tokens[i] == "-p" || tokens[i] == "-path") {
					wpath = !wpath;
				}
				else if (tokens[i] == "-s" || tokens[i] == "-size") {
					wsize = !wsize;
				}
				else if (tokens[i] == "-f" || tokens[i] == "-find") {
					if (tokens.size() < i + 1) {
						return false;
					}
					else {
						searchName = tokens[i + 1];
						i += 1;
					}
				}
				else if (tokens[i] == "-sl" || tokens[i] == "-searchLength") {
					if (tokens.size() < i + 1) {
						return false;
					}
					else {
						sizeSearchFrom = std::stoi(InternalFsys::splitTokens(":",tokens[i + 1])[0]);
						sizeSearchTo = std::stoi(InternalFsys::splitTokens(":", tokens[i + 1])[1]);
						i += 1;
					}
				}
			}
			else if (tokens[i][0] == '*') {
				tokens[i].erase(tokens[i].begin());
				std::string tpath;
				for (size_t j = i; j < tokens.size(); ++j) {
					tpath += tokens[j];
				}
				if (tpath == "std") {
					tpath = Setup::pathtoDir;
				}
				filesystemPath lp = InternalFileVec::lastPath;
				InternalFileVec::update(tpath);
				filesystemPath tmp_path;
				size_t len;
				for (size_t j = 0; j < InternalFileVec::fileVec.size(); ++j) {
					if (searchName == "") {
						try {
							tmp_path = InternalFileVec::get(j, InternalFileVec::gT::PATHTYPE);
							len = fs::file_size(tmp_path);
							if (sizeSearchFrom == 0 && sizeSearchTo == 0) {
								if (wpath) {
									std::cout << "path: \"" << tmp_path << "\"; ";
								}
								std::cout << "name: \"" << InternalFileVec::get(j, InternalFileVec::gT::FILENAMETYPE);
								if (wsize) {
									std::cout << "\"; size: " << len / 1000 << "KB";
								}
								std::cout << "\n";
							}
							else if (len > sizeSearchFrom && len < sizeSearchTo) { //search size
								if (wpath) {
									std::cout << "path: \"" << tmp_path << "\"; ";
								}
								std::cout << "name: \"" << InternalFileVec::get(j, InternalFileVec::gT::FILENAMETYPE);
								if (wsize) {
									std::cout << "\"; size: " << len / 1000 << "KB";
								}
								std::cout << "\n";
							}
						}
						catch (fs::filesystem_error& err) {

						}
					}
					else { //searchKey != ""
						filesystemPath tfilename;
						try {
							tfilename = InternalFileVec::get(j, InternalFileVec::gT::FILENAMETYPE);
							if (tfilename == searchName) { //found
								tmp_path = InternalFileVec::get(j, InternalFileVec::gT::PATHTYPE);
								len = fs::file_size(tmp_path);
								if (sizeSearchFrom == 0 && sizeSearchTo == 0) {
									if (wpath) {
										std::cout << "path: \"" << tmp_path << "\"; ";
									}
									std::cout << "name: \"" << InternalFileVec::get(j, InternalFileVec::gT::FILENAMETYPE);
									if (wsize) {
										std::cout << "\"; size: " << len / 1000 << "KB";
									}
									std::cout << "\n";
								}
								else if (len > sizeSearchFrom && len < sizeSearchTo) { //search size
									if (wpath) {
										std::cout << "path: \"" << tmp_path << "\"; ";
									}
									std::cout << "name: \"" << InternalFileVec::get(j, InternalFileVec::gT::FILENAMETYPE);
									if (wsize) {
										std::cout << "\"; size: " << len / 1000 << "KB";
									}
									std::cout << "\n";
								}
							}
						}
						catch (fs::filesystem_error& err) {

						}
					}
				}

				InternalFileVec::update(lp);
				return true;
			}
		}
		return false; //fail, no path
	}
	
public:
	CommandFile(std::string path, std::string filename) {
		this->path = path;
		this->filename = filename;
	}

	void check() {
		read = InternalFsys::splitTokens(" ", InternalFsys::readNormal(path));
	}

	bool go() {
		//add commands here

		if (read[0] == "Cout") {
			return comCout(read);
		}
		else if (read[0] == "info") {
			return comInfo(read);
		}
		else if (read[0] == "Cat") {
			return comCat(read);
		}
		else if (read[0] == "Corr") {
			return comCorr(read);
		}
		else if (read[0] == "Ser") {
			return comSer(read);
		}
		
		return false; //no command found
	}

	void copen() {
		file.close();
	}
	void cclose() {
		file.open(path);
	}

	bool run() {
		cclose();
		copen();
		check();
		bool ret = go();
		cclose();
		return ret;
	}
};

/////////////////////////////
///		Little docs for the CommandFiles:
/// 
/// ---Cout
/// #Syntax
/// Cout *text
/// 
/// #Extras
///   -br
/// addes an \r befor the text
///   -bn
/// addes an \n after the text
/// 
/// #info
/// this command ignores all \n and other \<letter>
/// 
/// ---Corr
/// #Syntax
/// Corr len
/// 
/// #info
/// this command prints random letters (len = count of all letters)
/// 
/// ---Cat
/// #Synatx
/// Cat *path
/// 
/// #Extras
///   -del
/// clears the file after reading it
///   -as
/// you use it as something
///   -as fvar <key>
/// searchs in the file for the var-key and return the value of it
/// 
/// #info
/// this command opens a file and print it
/// 
/// ---Ser
/// #Syntax
/// Ser *path
/// 
/// #Extras
///   -p
/// enables the path output
///   -s
/// enables the filesize output
///   -sl <from>:<to>
/// shows only files with a size between <from> and <to>
///   -f <filename>
/// shows only files with the name <filename>
/// 
/// #info
/// Prints all files in a dir + extra steps
/// 
/// ---info
/// >Working on<
/// 
/// 
/// 
 


#endif