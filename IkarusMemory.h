#ifndef IKARUS_MEMORY_H
#define IKARUS_MEMORY_H

#include "InternalDef.h"
#include "InternalEventMap.h"
#include "InternalErrorLogger.h"
#include "InternalStatesChecker.h"
#include "storage.h"
#include <map>
#include <string>

namespace IkarusMemory {
	Stor IkarusMemory;
	std::map<std::string, int> IkarusOwnMap;

	template <typename T>
	bool ikarusRemember(T value) {
		for (size_t i = 0; i < IkarusMemory.get((T)1).size(); ++i) {
			if (IkarusMemory.getwa((T)1, i) == value) {
				return true;
			}
		}
		return false;
	
	}

	bool ikarusRemember(bool map, Events::Event Event) {
		return IkarusOwnMap[Event.id] == 0 ? false : true;
	}

	void mapUpdate() {
		IkarusOwnMap = InternalEventMap::EventMap;
	}
}

#endif
