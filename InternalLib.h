#ifndef INTERNAL_LIB_H
#define INTERNAL_LIB_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"

#include <string>
#include <vector>

namespace InternalLib {
	std::string sb(bool bool_);
	
	template<typename T>
	bool isIn(T value, std::vector<T> vec, int ignore = -1);

	bool between(float num, float min, float max);

	size_t searchForVal_i(tokenType str, std::string key);

	std::string searchForVal(tokenType str, std::string key);

}
namespace IL = InternalLib;

#endif