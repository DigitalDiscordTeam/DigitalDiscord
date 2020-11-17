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

int main() {
	Events::Event FirstRun("FirstRun", "1000");
	
	InternalFsys::FEvents::delIdInEventFile("test2.txt", "ggazz");

	system("pause");
}