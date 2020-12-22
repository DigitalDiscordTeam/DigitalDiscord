#ifndef INTERNAL_STATES_CHECKER_H
#define INTERNAL_STATES_CHECKER_H

#include "InternalDef.h"
#include "InternalSys.h"
#include "InternalErrors.h"
#include "InternalFsys.h"
#include "InternalErrorLogger.h"

namespace InternalStatCheck {
	/*
	std::string getfUsername() {
		try {
			return InternalFsys::retMap("Username");
		}
		catch (...) {
			throw MapIsNotStoragingError{};
			InternalErrLog::LogMain.append(time(NULL), "MapIsNotStoragingError");
		}
		if (!System::dirPathExits) {
			System::checkIfPaths();
		}
		if (!System::dirPathExits) {
			InternalErrLog::LogMain.append(time(NULL), "DirMakeError");
			throw DirMakeError{};
		}
		return InternalFsys::read("Username", System::pathtoDir + "test.txt");
	}
	*/

//working on....

	

}

#endif