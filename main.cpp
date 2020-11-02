#include "InternalFsys.h"
#include "StdSetup.h"
#include "InternalErrorLogger.h"
#include "InternalEvents.h"
#include "InternalEventHandler.h"

#include <experimental/filesystem>

using InternalErrLog::LogMain;

int main() {
	LogMain.append(time(NULL), "TestErr");
	LogMain.append(time(NULL), "TestErr2");

	LogMain.printErr();
	std::cout << Setup::getSysUsername_s() << "\n";
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