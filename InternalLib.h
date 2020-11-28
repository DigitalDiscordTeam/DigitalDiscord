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
}
namespace IL = InternalLib;

#endif