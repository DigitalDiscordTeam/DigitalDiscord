#ifndef INTERNAL_LIB_H
#define INTERNAL_LIB_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"

#include <string>
#include <vector>

namespace InternalLib {
	std::string sb(bool bool_);

	bool between(float num, float min, float max);

	size_t searchForVal_i(tokenType str, std::string key);

	std::string searchForVal(tokenType str, std::string key);

	namespace random {
		int randomint();

		template<typename T>
		T randomChoice(T arr[]);

		template<typename T>
		T randomChoice(std::vector<T> arr);
	}
}
namespace IL = InternalLib;

#endif