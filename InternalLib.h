#ifndef INTERNAL_LIB_H
#define INTERNAL_LIB_H

#include "InternalDef.h"

#include <string>
#include <vector>

namespace InternalLib {
	std::string sb(bool bool_) { //string-bool
		return bool_ ? "true" : "false";
	}
	
	template<typename T>
	bool isIn(T value, std::vector<T> vec, int ignore = -1) {
		for (size_t i = 0; i < vec.size(); ++i) {
			if (ignore == -1) {
				if (value == vec[i]) {
					return true;
				}
			}
			else {
				if (i != ignore && value == vec[i]) {
					return true;
				}
			}
		}
		return false;
	}

	bool between(float num, float min, float max) {
		return (num > min && num < max);
	}

	size_t searchForVal_i(tokenType str, std::string key) { //return the index in the str
		for(size_t i = 0; i < str.size(); ++i) {
			if(str[i] == key) {
				return i+2;
			}
		}
	}
	std::string searchForVal(tokenType str, std::string key) {
		for(size_t i = 0; i < str.size(); ++i) {
			if(str[i] == key) {
				return str[i+2];
			}
		}
	}

}
namespace IL = InternalLib;

#endif