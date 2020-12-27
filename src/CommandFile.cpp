#include "CommandFile.h"

bool CommandFile::comCat(tokenType tokens) {
	isEght(tokens);
	bool asFvar = false;
	bool trunc = false;
	std::string varkey = "";
	for (size_t i = 1; i < read.size(); ++i) {
		try {
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

				//assert(System::dirPathExits);

				if (asFvar) {
					if (trunc) {
						std::string ret = InternalFsys::read(varkey, System::pathtoDir + read[i]);
						std::ofstream ofile;
						ofile.open(read[i], std::ios::trunc);
						ofile.close();
						std::cout << ret;
						return true;
					}
					else {
						std::cout << InternalFsys::read(varkey,System::pathtoDir + read[i]);
						return true;
					}
				}
				if (trunc) {
					std::string ret = InternalFsys::readNormal(System::pathtoDir + read[i]);
					std::ofstream ofile;
					ofile.open(System::pathtoDir + read[i], std::ios::trunc);
					ofile.close();
					std::cout << ret;
					return true;
				}
				std::cout << InternalFsys::read(varkey, System::pathtoDir + read[i]);
				return true;
			}
		}
		catch(...) {

		}
	}
	return false; //no filename given
}

bool CommandFile::comCorr(tokenType tokens) { //corrupted line
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

bool CommandFile::comCout(tokenType tokens) {
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

bool CommandFile::comSer(tokenType tokens) {
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
				tpath = System::pathtoDir;
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
					catch (...) {

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
					catch (...) {

					}
				}
			}
			try {
				InternalFileVec::update(lp);
			}
			catch(...) {}
			return true;
		}
	}
	return false; //fail, no path
}

CommandFile::CommandFile(std::string path, std::string filename) {
	this->path = path;
	this->filename = filename;
}

void CommandFile::check() {
	read = InternalFsys::splitTokens(" ", InternalFsys::readNormal(path));
}

bool CommandFile::go() {
	//add commands here

	if (read[0] == "Cout") {
		return comCout(read);
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

void CommandFile::copen() {
	file.open(path);
}

void CommandFile::cclose() {
	file.close();
}

bool CommandFile::run() {
	cclose();
	copen();
	check();
	cclose();
	return go();
}