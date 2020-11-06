#ifndef INTERNAL_STATES_CHECKER_H
#define INTERNAL_STATES_CHECKER_H

#include "InternalDef.h"
#include "StdSetup.h"
#include "InternalErrors.h"
#include "InternalFsys.h"
#include "InternalErrorLogger.h"

namespace InternalStatCheck {
	std::string getfUsername() {
		try {
			return InternalFsys::retMap("Username");
		}
		catch (...) {
			throw MapIsNotStoragingError;
			InternalErrLog::LogMain.append(time(NULL), "MapIsNotStoragingError");
		}
		if (!Setup::dirPathExits) {
			Setup::checkIfPaths();
		}
		if (!Setup::dirPathExits) {
			InternalErrLog::LogMain.append(time(NULL), "DirMakeError");
			throw DirMakeError;
		}
		return InternalFsys::read("Username", Setup::pathtoDir + "\\test.txt\\"); //TODO: Linux stuff
	}

	

}

#endif