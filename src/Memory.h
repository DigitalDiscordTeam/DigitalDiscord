#ifndef MEMORY_H_DD
#define MEMEORY_H_DD

#include "InternalDef.h"
#include "Cryp.h"
#include "InternalLib.h"
#include "InternalPrettyConsoleOut.h"

#include <vector>
#include <string>
#include <map>
#include <assert.h>
#include <algorithm>

namespace Memory {

	class Data  {
	public:
		int crypCount = 0;
		std::string data;
		std::map<std::string,int> compreMap; //temp, counts how often an pair was found
		std::vector<char> split;
		std::map<std::string, std::string> decodeMap; //after:before
		std::map<std::string,std::string> decodeMap2; //before:after

		Data(std::string data);

		void operator=(Data data);
		void operator=(std::string data);
		void operator=(const char* data);

		void initSplit();

	};

	void searchPairs(Data& data);

	void compre(Data& data);

	void recompre(Data& data);

	void factCheck(Data& data);
}

#endif