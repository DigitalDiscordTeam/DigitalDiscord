#ifndef INTERNAL_LIB_H
#define INTERNAL_LIB_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"

#include <string>
#include <vector>

namespace InternalLib {

	
	class c_VOID {
		//void
	public:

		c_VOID() {}

		c_VOID(int) {}


	};
	
	std::string sb(bool bool_);

	bool between(float num, float min, float max);

	size_t searchForVal_i(tokenType str, std::string key);

	std::string searchForVal(tokenType str, std::string key);

	namespace random {
		int randomint();

		template<typename T>
		MDEF T randomChoice(T arr[]) {
			return arr[randomint()%sizeof(arr)];
		}

		template<typename T>
		MDEF T randomChoice(std::vector<T> arr) {
			return arr[randomint()%arr.size()];
		}
	}
}
namespace IL = InternalLib;

#endif