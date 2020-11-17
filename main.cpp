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
#include "CommandFileClass.h"

int main() {
	CommandFile cF("test3.txt", "test3.txt");
	cF.check();
	cF.go();
	system("pause");
}