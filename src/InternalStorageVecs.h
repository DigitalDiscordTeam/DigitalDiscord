#ifndef INTERNAL_STORAGE_VECS_H
#define INTERNAL_STORAGE_VECS_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalSys.h"
#include "InternalErrors.h"

#include <stdlib.h>
#include <string>
#include <vector>

namespace InternalFileVec {
	inline const std::string home = System::pathtoDir;
	inline const std::wstring whome = System::pathtoDir_w;
	std::vector<fs::path> get(fs::path path);
}	

namespace InternalDirVec {
	inline const std::string home = System::pathtoDir;
	inline const std::wstring whome = System::pathtoDir_w;
	std::vector<fs::path> get(fs::path path);
}

#endif