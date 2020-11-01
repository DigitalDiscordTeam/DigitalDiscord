#include "InternalFsys.h"
#include "StdSetup.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"
#include "InternalEventHandler.h"

using InternalErrLog::LogMain;

int main() {
	LogMain.append(time(NULL), "TestErr");
	LogMain.append(time(NULL), "TestErr2");

	LogMain.printErr();
	std::cout << Setup::getcurretUsername_s() << "\n";
	InternalEventHandler::trigger(Event::Spam);
	InternalEventHandler::trigger(Event::Spam);
	system("pause");
}

/*
X = Hallo
Y = ollaH
Z = 42
Hallo = X
*/