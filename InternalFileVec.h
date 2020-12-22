#ifndef INTERNAL_FILE_VEC_H
#define INTERNAL_FILE_VEC_H

#include "InternalDef.h"
#include "InternalErrorLogger.h"
#include "InternalSys.h"
#include "InternalErrors.h"

#include <stdlib.h>
#include <string>
#include <vector>

namespace InternalFileVec {
	std::vector<std::pair<filesystemPath, std::string>> fileVec; // path : filename
	filesystemPath lastPath;

	void update(const filesystemPath path);

	enum class getType { PATHTYPE, FILENAMETYPE };
	using gT = getType;

	filesystemPath get(std::string value, gT type);

	filesystemPath get(size_t index, gT type);
}

#endif