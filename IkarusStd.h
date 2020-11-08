#ifndef IKARUS_STD_H
#define IKARUS_STD_H

#include "InternalDef.h"
#include "storage.h"
#include "InternalEventMap.h"
#include "IkarusCout.h"

namespace Ikarus {
	Stor IkarusMemory;

	namespace ConOut = IkarusCout;

	void boot() {
		ConOut::IkarusSP.setSleeptime(1000);
	}

	/*
	template <typename T>
	bool ikarusRemember(T value) {
		if (T == int) {
			for (size_t i = 0; i < IkarusMemory.get((int)1).size(); ++i) {

			}
		}
	}
	*/
}

#endif
