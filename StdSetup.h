#ifndef STD_SETUP_H
#define STD_SETUP_H

#include "InternalErrors.h"
#include "InternalFsys.h"
#include "InternalDef.h"

#ifdef USE_WIN_
#include <sys\stat.h>
#include <string>
#include <Windows.h>
#include <lmcons.h>
#include <stdlib.h>
#endif

#ifdef USE_LINUX_
#include <iostream>
#include <string>
#include <lmcons.h>
#include <stdlib.h>
#endif 

namespace Setup {
	std::string pathtoDir = "";
	std::wstring pathtoDir_w = L"";
#ifdef USE_WIN_

	std::string getSysUsername_s() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);

		std::wstring tmp = username;
		std::string ret(tmp.begin(), tmp.end());
		return ret;
	}

	std::wstring getSysUsername_w() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);

		return username;
	}

	void createFiles() {

		std::wstring path;
		path += L"C:\\Users\\";
		path += getSysUsername_w();
		path += L"\\%APPDATA%\\DigitalDiscord";

		if (std::experimental::filesystem::exists(path)) {

			if (!std::experimental::filesystem::create_directory(path)) {
				throw DirMakeError;
			}
		}

		Setup::pathtoDir_w = path;
		Setup::pathtoDir = "C:\\Users\\" + getSysUsername_s() + "\\%APPDATA%\\DigitalDiscord";
	}


#endif //USE_WIN_

#ifdef USE_LINUX_
	std::string getSysUsername_s() {
		return (std::string)getenv("USERNAME");
	}

	std::wstring getSysUsername_w() {
		return (std::wstring)getenv("USERNAME");
	}

	void createFiles() {

		std::wstring path;
		path += L"~/.config/DigitalDiscord";

		if (std::experimental::filesystem::exists(path)) {

			if (!std::experimental::filesystem::create_directory(path)) {
				throw DirMakeError;
			}
		}
		Setup::pathtoDir_w = path;
		Setup::pathtoDir = "~/.config/DigitalDiscord"
	}

#endif //USE_LINUX_
}


#endif
