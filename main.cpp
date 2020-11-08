#include "InternalDef.h"
#include "InternalStatesChecker.h"
#include "InternalFsys.h"
#include "StdSetup.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"
#include "InternalPrettyConsoleOut.h"
#include "InternalEventMap.h"
#include "IkarusStd.h"

#include <experimental/filesystem>

using InternalErrLog::LogMain;

int main() {
	Setup::checkIfPaths();
	InternalFsys::makeFile("test.txt", Setup::pathtoDir, "This is a file lol\n");

	system("pause");

}

/*
X = Hallo
Y = ollaH
Z = 42
Hallo = X
*/