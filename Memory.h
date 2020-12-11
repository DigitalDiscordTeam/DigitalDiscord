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

namespace Memory {

	class Data {
	public:
		int crypCount = 0;
		std::string data;
		std::map<std::string,int> compreMap; //temp, counts how often an pair was found
		std::vector<char> split;
		std::map<std::string, std::string> decodeMap; //after:before
		std::map<std::string,std::string> decodeMap2; //before:after

		Data(std::string data) {
			this->data = data;
		}

		void operator=(Data data) {
			this->data = data.data;
		}
		void operator=(std::string data) {
			this->data = data;
		}
		void operator=(const char* data) {
			this->data = data;
		}

		void initSplit() {
			split.clear();
			for (size_t i = 0; i < data.size(); ++i) {
				split.push_back(data[i]);
			}
		}

	};

	void searchPairs(Data& data) {
		if (data.data == "") {
			return;
		}
		data.compreMap.clear();
		data.split.clear();
		data.initSplit();
		/*
		* for explaining: every time the char in the vector adds the string that is the char + 1 & -1 a number of 1.
		* if this count is higher than 1, the post-process can use that!
		*/
		for (size_t i = 0; i < data.split.size(); ++i) {
			if (i+1 != data.split.size()) {
				data.compreMap[(std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])))] += 1;
			}
		}
	}

	void compre(Data& data) {
		data.crypCount += 1;
		searchPairs(data);
		data.decodeMap.clear();
		data.decodeMap2.clear();
		std::string tmpString = "";
		int tmpRand = 0;
		for (size_t i = 0; i < data.split.size(); ++i) { //works with the data.compreMap 
			DEBUG_START_
				if (i + 1 != data.split.size()) {
					std::cout << i << ":" << (std::string(1, data.split[i]) + (std::string(1, data.split[i + 1]))) << "\n";
				}
			DEBUG_END_
			if (i + 1 != data.split.size() && data.decodeMap[(std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])))] != "") { //known
				DEBUG_START_
					std::cout << "[DEBUG] one thing found! (i:" << i << "); data:" << (std::string(1, data.split[i]) + (std::string(1, data.split[i + 1]))) << "\n";
				DEBUG_END_
				tmpString = data.decodeMap[(std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])))];
				data.split.erase(data.split.begin() + i);
				data.split[i] = tmpString[0]; ///only one char to avoid bugs
				--i; //set i back because the index behind i is changed
			}
			if (i+1 != data.split.size() && data.compreMap[(std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])))] > 1) {
				DEBUG_START_
					std::cout << "[DEBUG] compre found, (i:" << i << "); data:" << (std::string(1,data.split[i]) + (std::string(1, data.split[i+1]))) << "\n";
				DEBUG_END_
				while (INFINITY_LOOP) {
					srand(time(NULL) + (rand() % time(NULL)));
					tmpRand = ((rand() % 255) + 126); //only special keys
					if(InternalLib::isIn(static_cast<char>(tmpRand),data.split)) {
						continue;
					}
					DEBUG_START_
						std::cout << "tmpRand:" << tmpRand << "\n";
					DEBUG_END_
					if (data.decodeMap2[std::string(1,static_cast<char>(tmpRand))] != "") { //this key is already in the map
						DEBUG_START_
							std::cout << "[DEBUG] compre, key is the the map, key:" << static_cast<char>(tmpRand) << "\n";
						DEBUG_END_
						continue;
					}
					data.decodeMap[(std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])))] = std::string(1,static_cast<char>(tmpRand));
					data.decodeMap2[std::string(1,static_cast<char>(tmpRand))] = (std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])));
					DEBUG_START_
						std::cout << "[DEBUG] compre, key:" << static_cast<char>(tmpRand) << " map: " << data.decodeMap[(std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])))] << "\n";
					DEBUG_END_
					break;
				}
				data.split.erase(data.split.begin() + i);
				data.split[i] = static_cast<char>(tmpRand);
				--i;
			}
		}
		std::string endData = "";
		for (size_t i = 0; i < data.split.size(); ++i) {
			endData += data.split[i];
		}
		data.data = endData;
		endData = "";
		EXIT_WITH(0);
		return;
	}

	void recompre(Data& data) {
		ERROR_IF(data.data == "");
		int rounds = 0;
		char tmpChar = ' ';
		char tmpChar2 = ' ';
		data.initSplit();

		for (size_t i = 0; i < data.split.size(); ++i) {
			DEBUG_START_
				std::cout << "[DEBUG] loop (recompre) i:" << i << " | thing:" << data.split[i] << " | map:" << data.decodeMap[(std::string(1,data.split[i]))] << " | map2:" << data.decodeMap2[std::string(1,data.split[i])] << " | len of both: " << data.decodeMap2[std::string(1,data.split[i])].length() + data.decodeMap[std::string(1,data.split[i])].length() << "\n";
			DEBUG_END_
			ERROR_IF(data.decodeMap2[std::string(1,data.split[i])] == "");
			if (data.decodeMap2[std::string(1,data.split[i])] != "") { //a thing to encryp has been found
				ERROR_IF(data.decodeMap2[std::string(1,data.split[i])] == "");
				DEBUG_MESSAGE("found (recompre) i:" << i << " | thing:" << data.split[i] << " | map:" << data.decodeMap[std::string(1, data.split[i])] << " | map2:" << data.decodeMap2[std::string(1,data.split[i])] << " | len of both: " << data.decodeMap2[std::string(1,data.split[i])].length() + data.decodeMap[std::string(1,data.split[i])].length() <<"\n");
				if (i + 1 <= data.split.size()) {
					DEBUG_MESSAGE("(recompre) i + 1 <= data.split.size()!\n");
					tmpChar = data.split[i]; 
					DEBUG_MESSAGE("tmpChar:" << tmpChar)
					data.split[i] = data.decodeMap2[std::string(1, tmpChar)][0];
					++i;
					char tmp = data.decodeMap2[std::string(1, tmpChar)][1];
					data.split.insert(data.split.begin() + i, tmp);
					DEBUG_MESSAGE("instered \"" << data.split[i] << "\"; at:" << i)
					++i;
				}
				else {
					DEBUG_MESSAGE(" (recompre) i + 1 > data.split.size()!\n");
					tmpChar = data.split[i+1];
					data.split[i] = data.decodeMap2[std::string(1, data.split[i])][0];
					data.split.push_back(data.decodeMap2[std::string(1, tmpChar)][0]);
					i = data.split.size(); //end
				}
				tmpChar = ' ';
				tmpChar2 = ' ';
			}
			if(!i < data.split.size() && !rounds == 3) {
				DEBUG_MESSAGE("startet second time to loop...")
				++rounds;
				i = 0;
				continue;
			}
		}
		data.decodeMap.clear();
		data.decodeMap2.clear();
		data.crypCount -= 1;
		data.compreMap.clear();
		
		std::string endData;
		for (size_t i = 0; i < data.split.size(); ++i) {
			endData += data.split[i];
		}
		data.data = "";
		data.data = endData;
		return;
	}

	void factCheck(Data& data) {
		for(size_t i = 0; i < data.data.size(); ++i) {
			std::cout << "data[" << i << "]: " << data.data[i] << "\n";
		}
		std::cout << "splitInit:" << !data.split.empty() << "\n";

		for(size_t i = 0; i < data.data.size(); ++i) {
			std::cout << "map1[" << data.data[i] << "]: " << data.decodeMap[std::string(1,data.data[i])] << "\n";
			std::cout << "map2[" << data.data[i] << "]: " << data.decodeMap2[std::string(1,data.data[i])] << "\n";
		}
	}
}

#endif