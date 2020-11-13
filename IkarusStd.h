#ifndef IKARUS_STD_H
#define IKARUS_STD_H

#include "InternalDef.h"
#include "storage.h"
#include "InternalEventMap.h"
#include "IkarusCout.h"
#include "IkarusMemory.h"

namespace Ikarus {
	namespace ConOut = IkarusCout;
	namespace Memory = IkarusMemory;

	void boot() {
		ConOut::IkarusSP.setSleeptime(1000);
		Memory::mapUpdate();
	}

}

#endif
