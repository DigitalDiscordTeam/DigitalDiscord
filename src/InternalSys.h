#ifndef STD_INTERNAL_SYSTEM_H
#define STD_INTERNAL_SYSTEM_H

#include "InternalDef.h"
#include "InternalErrors.h"
#include "InternalErrorLogger.h"

#ifdef USE_WIN_
#include <sys\stat.h>
#include <string>
#include <Windows.h>
#include <lmcons.h>
#include <stdlib.h>
#include <codecvt>
#endif

#ifdef USE_LINUX_
#include <codecvt>
#include <string>
#include <stdlib.h>
#include <cstring>
#endif 

namespace System {
	MDEF bool dirPathExits;
	MDEF std::string pathtoDir;
	MDEF std::wstring pathtoDir_w;

	std::wstring string2wsstring(const std::string& str);

	std::string wstring2string(const std::wstring& wstr);

	std::string getSysUsername_s();

	std::wstring getSysUsername_w();

	void checkIfPaths();

	void createPath();

} //namespace InternalFSys


#endif
