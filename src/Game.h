#ifndef GAME_H
#define GAME_H

#include "InternalDef.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalErrors.h"
#include "InternalSys.h"
#include "InternalFsys.h" 
#include "Chars.h"
#include "InternalFileVec.h"
#include "ExternalPlugins.h"
#include "InternalRoadVal.h"

//#include <pthread.h>

namespace Game {
	
	void update();

	void start(bool showcase = false, int sleepTime = 500);
}
#endif