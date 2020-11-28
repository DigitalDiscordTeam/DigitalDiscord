#ifndef MEMORY_H_DD
#define MEMEORY_H_DD

#include "InternalDef.h"
#include "Cryp.h"
#include "InternalLib.h"
#include "InternalPrettyConsoleOut.h"

#include <vector>
#include <string>
#include <map>

namespace Memory {
	std::vector<char> normalLetters;

	void normalVecInit() {
		//rewite pls
	}

	class Data {
	public:
		int crypCount = 0;
		std::string data;
		std::map<std::string,int> compreMap; //temp, counts how often an pair was found
		std::vector<char> split;
		std::map<std::string, std::string> decodeMap; //after:before

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
					srand(time(NULL));
					tmpRand = ((rand() % 255) + 126); //only special keys
					DEBUG_START_
						std::cout << "tmpRand:" << tmpRand << "\n";
					DEBUG_END_
					if (data.decodeMap.count(std::string(1,static_cast<char>(tmpRand))) != 0) { //this key is already in the map
						DEBUG_START_
							std::cout << "[DEBUG] compre, key is the the map, key:" << static_cast<char>(tmpRand) << "\n";
						DEBUG_END_
						continue;
					}
					data.decodeMap[(std::string(1, data.split[i]) + (std::string(1, data.split[i + 1])))] = std::string(1,static_cast<char>(tmpRand));
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
		return;
	}

	void recompre(Data& data) {
		assert(data.data == "" || !data.decodeMap.empty());
		data.initSplit();

		for (size_t i = 0; i < data.split.size(); ++i) {
			if (data.decodeMap.count(std::string(1, data.split[i])) != 0) { //a thing to encryp has been founded
				if (i + 2 < data.split.size()) {
					data.split.insert(data.split.begin() + i, data.decodeMap[std::string(1, data.split[i])][0]);
					++i;
					data.split.insert(data.split.begin() + i, data.decodeMap[std::string(1, data.split[i])][1]);
					++i;
				}
				else {
					data.split.push_back(data.decodeMap[std::string(1, data.split[i])][0]);
					data.split.push_back(data.decodeMap[std::string(1, data.split[i])][0]);
					i = data.split.size(); //end
				}
			}
		}
		data.decodeMap.clear();
		data.crypCount -= 1;
		data.compreMap.clear();
		
		std::string endData;
		for (size_t i = 0; i < data.split.size(); ++i) {
			endData += data.split[i];
		}
		data.data = endData;
		return;
	}
}

#endif