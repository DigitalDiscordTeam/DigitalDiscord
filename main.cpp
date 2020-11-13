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

#include <experimental/filesystem>

using InternalErrLog::LogMain;

int main() {
	std::string test("Hallo");
	Cryp::caeser(test);
	std::cout << test << "\n";
	Cryp::caeser(test, true);
	std::cout << test << "\n";

	system("pause");

}