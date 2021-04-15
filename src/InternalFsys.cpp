#include "InternalFsys.h"

std::streamsize InternalFsys::get_flength(std::ifstream& file) {
	if(!file.is_open()) {
		throw ReadFileError{};
	}
	std::streampos temp_1 = file.tellg();
	file.seekg(0, std::fstream::end);
	std::streampos temp_2 = file.tellg();
	file.seekg(temp_1, std::fstream::beg);

	return temp_2;
}

std::string InternalFsys::retMap(std::string value) {
	if (MyMapStor[value] == "") {
		throw MapIsNotStoragingError{};
	}
	else {
		return MyMapStor[value];
	}
}

std::string InternalFsys::getFileType(std::string path) {
	bool sw; //switch
	std::string str;
	for(size_t i = 0; i < path.size(); ++i) {
		if(sw) {
			str += path[i];
		}
		else if(path[i] == '.') {
			sw = true;
		}
	}
	return str;
}

bool InternalFsys::fileExitCheck(const std::string path) {
	return fs::exists(path);
}

bool InternalFsys::is_empty(std::ifstream& pFile) {
	return pFile.peek() == std::ifstream::traits_type::eof();
}

std::string InternalFsys::read(std::string key, std::string path) {
	std::string re = readNormal(path);
		
	std::vector<std::string> vec;
	std::string tmp;
	bool inLstr; //search for a multiline string called with ""
	for (size_t i = 0; i < re.length(); ++i) {
		if(re[i] == '\"') {
			inLstr = !inLstr;
			++i;
		}
		if(re[i] == '/') {
			try {
				if(key.substr(key.size()-6,key.size()) != "NO_REP") {
					tmp += "\n";
					continue;
				}
			}
			catch(std::exception& err) {
				tmp += "\n";
				InternalErrLog::LogMain.append(time(NULL),err.what());
				continue;
			}
			
		}
		if (!inLstr && (re[i] == ' ' || re[i] == '\n' || re[i] == '\0' || re[i] == ';')) {
			vec.push_back(tmp);
			tmp = "";
		}
		else if (re[i] != '\r') {
			tmp += re[i];
		}
	}
	vec.push_back(tmp);
	for(size_t i = 0; i < vec.size(); ++i) {
		if(vec[i] == "") {
			vec.erase(vec.begin() + i);
			--i;
			DEBUG_MESSAGE("deleted a \"\" in vec[" << i << "]")
		}
	}
	int counter = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		if ((counter + 3) % 3 == 0 && vec[i] == key) {
			MyMapStor[key] = vec[i + 2];
			return vec[i + 2];
		}

		DEBUG_MESSAGE("(read()) loop failed, i:" << i << " value:" << vec[i] << " key: " << key)
		counter += 1;
	}
	try {
		std::string ret;
		ret = read(key + "NO_REP",path);
		return ret;
	}
	catch(ValueNotFoundError& err) {
		InternalErrLog::LogMain.append(time(NULL),err.toString());
	}
	throw ValueNotFoundError{}; //the value is not in the file
}

void InternalFsys::delStor(std::string value) {
	if (MyMapStor[value] != "") {
		MyMapStor[value] = "";
	}
	else {
		throw MapIsNotStoragingError{};
	}
}

tokenType InternalFsys::splitTokens(const std::string splitKey, const std::string string, void(*fun)(const char& i, std::string& str)) {
	/* usage:
		---  splitTokens("key|key2|key3|...",string);

		--- This function split the the string into tokens by the given keys
	*/
		
	if (string == "") {
		return std::vector<std::string>();
	}

	std::vector<char> keys;
	if (splitKey.length() != 1) {
		std::string splitKey2 = (splitKey[splitKey.length()] == '|' ? splitKey:(splitKey + "|"));
		int check = 0;
		for (size_t i = 0; i < splitKey2.length(); ++i) {
			check += 1;
			if (splitKey2[i] == '|') {
				keys.push_back(splitKey2[i - 1]);
				check = 0;
			}
			if (check % 2 == 0 && check != 0) {
				throw InvaildInputError{};
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
		fun(string[i],tmp);
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

void InternalFsys::resetFiles(bool createAsNew) {
	if (System::pathtoDir == "") {
		InternalErrLog::LogMain.append(time(NULL), "ResetFilesError");
		throw ResetFilesError{};
	}
	else {
		
		//soon
	}
}

std::string InternalFsys::readNormal(std::string path) {
	std::ifstream ifile;
	ifile.open(path, std::ios::binary);
	if(!ifile.is_open()) {
		ifile.close();
		throw OpenFileError{};
	}
	if (InternalFsys::is_empty(ifile)) {
		ifile.close();
		return "";
	}
	std::streamsize len = get_flength(ifile);
	char* dummy = new char[len];

	try {
		ifile.read(dummy, len);
	}
	catch(std::exception& err) {
		ifile.close();
		throw ReadFileError{};
	}
	if (dummy == nullptr || strlen(dummy) == 0) {
		ifile.close();
		throw ReadFileError{};
	}
	ifile.close();
	//dummy += '\0';
	std::string re;
	re.assign(dummy, len);

	delete[] dummy;
	dummy = nullptr;

	return re;
}

void InternalFsys::write(std::string path, std::string key, std::string newValue) {
	std::string read = InternalFsys::readNormal(path);

	tokenType readSplit = InternalFsys::splitTokens(" |\n|",read);
	size_t index = InternalLib::searchForVal_i(readSplit,key);
	DEBUG_MESSAGE("index: " << index << ";");
	readSplit[index] = newValue;

	std::ofstream ofile;
	ofile.open(path, std::ios::trunc);
	if(!ofile.is_open()) {
		ofile.close();
		throw OpenFileError{};
	}

	for(size_t i = 0; i < readSplit.size(); ++i) {
		ofile << readSplit[i];

		ofile << " ";

	}
	ofile.close();
}

void InternalFsys::writeNormal(std::string path, std::string value, bool trunc) {
	std::ofstream ofile;
	ofile.open(path, trunc ? std::ios::trunc : std::ios::ate);
	if(!ofile.is_open()) {
		ofile.close();
		throw OpenFileError{};
	}
	ofile.write(value.c_str(),value.size());
	ofile.close();
}

bool InternalFsys::sys::makeFile(std::string name, std::string path, std::string message) {
	if (fs::exists(path + name)) {
		InternalErrLog::LogMain.append(time(NULL), "FileIsAlreadyExistingError");
		throw FileIsAlreadyExistingError{};
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

void InternalFsys::sys::deleteFile(std::string name, std::string path) {
	if(!fs::remove(path + name)) {
		throw OpenFileError{};
	}
}

void InternalFsys::sys::makeDir(std::string names) {
	if(!fs::create_directory(System::pathtoDir + names)) {
		throw DirMakeError{};
	}	
}

void InternalFsys::sys::deleteDir(std::string path) {
	if(!fs::remove(path)) {
		throw DeleteDirError{};
	}
}

tokenType InternalFsys::readVec(std::string path, std::string key) {
	std::string re = read(key,path);
	re.erase(re.begin());
	re.erase(re.begin()+re.size()-1);
	DEBUG_MESSAGE("re = " << re)
	tokenType tokens = splitTokens(",",re);
	DEBUG_MESSAGE("size: " << tokens.size())
	
	if(key.substr(key.size()-6,key.size()) != "_NOREM") {
		for(size_t i = 0; i < tokens.size(); ++i) {
			if(tokens[i] == "") {
				tokens.erase(tokens.begin()+i);
			}
		}
	}
	return tokens;
}

void InternalFsys::writeVec(std::vector<std::string> vec,std::string path, std::string key) {
	std::string ret = "{";
	for(auto& i : vec) {
		if(key.substr(key.size()-6,key.size()) != "_NOREM" && i == "") {
			continue;
		}
		ret += i + ",";
	}
	ret.erase(ret.find_last_of(',')); //delete the last ","
	ret += "}";
	write(path,key,ret);	
}

void InternalFsys::addToVec(std::string path, std::string key, std::string val) {
	tokenType tokens = readVec(path,key);
	tokens.push_back(val);
	writeVec(tokens,path,key);
}

std::string InternalFsys::readLine(std::string path, size_t line) {
	return splitTokens("\n|/|",readNormal(path))[line];
}