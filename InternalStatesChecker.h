#ifndef INTERNAL_STATES_CHECKER_H
#define INTERNAL_STATES_CHECKER_H

#include "InternalErrors.h"
#include "InternalFsys.h"
#include "InternalErrorLogger.h"

#include <lmcons.h>
#include <Windows.h>

namespace InternalStatCheck {
	std::string getfUsername() {
		try {
			std::string ret = InternalFsys::retMap("Username");
			return ret;
		}
		catch (MapIsNotStoragingErrorc& err) {
			InternalErrLog::LogMain.append(time(NULL), "MapIsNotStoragingError");
		}
		return InternalFsys::read("Username", "test.txt");
	}

}

#endif