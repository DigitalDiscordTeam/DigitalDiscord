#include "InternalLib.h"

std::string InternalLib::sb(bool bool_) { //string-bool
	return bool_ ? "true" : "false";
}

bool InternalLib::between(float num, float min, float max) {
	return (num > min && num < max);
}

size_t InternalLib::searchForVal_i(tokenType str, std::string key) { //return the index in the str
	for(size_t i = 0; i < str.size(); ++i) {
		if(str[i] == key) {
			return i+2;
		}
	}
	throw ValueNotFoundError{};
	return -1;
}

std::string InternalLib::searchForVal(tokenType str, std::string key) {
	for(size_t i = 0; i < str.size(); ++i) {
		if(str[i] == key) {
			return str[i+2];
		}
	}
	throw ValueNotFoundError{};
	return "";
}