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
}

#endif
