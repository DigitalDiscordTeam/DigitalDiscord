#ifndef GAME_H
#define GAME_H

#include "InternalDef.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalErrors.h"
#include "InternalSys.h"
#include "InternalFsys.h" 
#include "Chars.h"
#include "InternalStorageVecs.h"
#include "ExternalPlugins.h"
#include "InternalRoadVal.h"
#include "SpeakBubbles.h"

namespace Game {
	void update();

	void start(bool showcase = false, int sleepTime = 500);
}
#endif