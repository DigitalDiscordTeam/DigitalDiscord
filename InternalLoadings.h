#ifndef INTERNAL_LOADINGS_H
#define INTERNAL_LOADINGS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "StdSetup.h"
#include "InternalFsys.h"

namespace InternalLoadings {
	void fillFsysMap() {
		InternalFsys::read("Username", Setup::pathtoDir);
	}

}

#endif
