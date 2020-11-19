#include "InternalDef.h"
#include "InternalStatesChecker.h"
#include "InternalFsys.h"
#include "InternalSys.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalEventMap.h"
#include "IkarusStd.h"
#include "Cryp.h"
#include "Game.h"

int main() {
	Game::start(true);
	InternalFsys::makeFile("test.txt", Setup::pathtoDir ,"get rick rolled lol\nlol2");
	system("pause");
}