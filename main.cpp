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
	InternalPCO::LoadingScreen screen(10, 0, false, '#'); 
	screen.next("boot ikarus...");
	Sleep(1000);
	screen.next("do stuff");
	
	system("pause");

}

/*
X = Hallo
Y = ollaH
Z = 42
Hallo = X
*/