#ifndef STD_SETUP_H
#define STD_SETUP_H

#include "InternalErrors.h"
#include "InternalFsys.h"

#include <sys\stat.h>
#include <string>
#include <Windows.h>
#include <lmcons.h>
#include <stdlib.h>

namespace Setup {

	std::string getcurretUsername_s() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);

		std::wstring tmp = username;
		std::string ret(tmp.begin(),tmp.end());
		return ret;
	}

	std::wstring getcurretUsername_w() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);

		return username;
	}

	void createFiles() {

		//make a dictionary pls :c

		std::wstring path;
		path += L"C:\\Users\\";
		path += getcurretUsername_w();
		path += L"\\Documents\\Testdir";

		if (_wmkdir(path.c_str()) == -1) {
			throw DirMakeError;
		}
	}
}

#endif
