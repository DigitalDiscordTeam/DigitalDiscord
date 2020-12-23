#ifndef INTERNAL_F_SYS_H
#define INTERNAL_F_SYS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalEventMap.h"
#include "InternalSys.h"
#include "InternalLib.h"

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

	MDEF std::map<std::string, std::string> MyMapStor;

	std::streamsize get_flength(std::ifstream& file);

	std::string retMap(std::string value);

	std::string getFileType(std::string path);

	bool fileExitCheck(const std::string path);

	bool is_empty(std::ifstream& pFile);

	std::string readNormal(std::string path);

	std::string read(std::string key, std::string path);

	void delStor(std::string value);

	tokenType splitTokens(const std::string splitKey, const std::string string);

	void resetFiles(bool createAsNew = false);

	std::string readNormal(std::string path);

	void write(std::string path, std::string key, std::string newValue);
}

#include "InternalEvents.h"

namespace InternalFsys {
	namespace FEvents {
		std::vector<std::string> readEventFile(std::string path);

		void writeIdInEventFile(std::string path, const std::string id, std::vector<std::string> read = std::vector<std::string>());

		void delIdInEventFile(std::string path, const std::string id);
	}

	namespace sys { 
		bool makeFile(std::string name, std::string path, std::string message = "");

		void makeDir(std::string names);
	}
}

#endif
