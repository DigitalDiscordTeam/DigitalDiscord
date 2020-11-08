#ifndef STD_SETUP_H
#define STD_SETUP_H

#include "InternalDef.h"
#include "InternalErrors.h"
#include "InternalFsys.h"
#include "InternalErrorLogger.h"
//#include "InternalEventMap.h"

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
#include <stdlib.h>
#include <cstring>
#endif 

namespace Setup {
	bool dirPathExits = false;
	std::string pathtoDir = "";
	std::wstring pathtoDir_w = L"";

	std::wstring string2wsstring(const std::string& str){
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}

	std::string wstring2string(const std::wstring& wstr)
	{
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}

#ifdef USE_WIN_

	std::string getSysUsername_s() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);

		std::wstring tmp = username;
		std::string ret = Setup::wstring2string(tmp);
		return ret;
	}

	std::wstring getSysUsername_w() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);

		return username;
	}

	void checkIfPaths() {
		if (std::experimental::filesystem::exists(L"C:\\Users\\" + getSysUsername_w() + L"\\AppData\\LocalLow\\DigitalDiscord\\")) {
			dirPathExits = true;
			pathtoDir_w = L"C:\\Users\\" + getSysUsername_w() + L"\\AppData\\LocalLow\\DigitalDiscord\\";
			pathtoDir = "C:\\Users\\" + getSysUsername_s() + "\\AppData\\LocalLow\\DigitalDiscord\\";
		}
		else {
			dirPathExits = false;
		}
	}

	void createFiles() {

		std::wstring path;
		path += L"C:\\Users\\";
		path += getSysUsername_w();
		path += L"\\AppData\\LocalLow\\DigitalDiscord\\";

		if (!std::experimental::filesystem::exists(path)) {

			if (!std::experimental::filesystem::create_directory(path)) {
				throw DirMakeError;
			}
		}

		Setup::pathtoDir_w = path;
		Setup::pathtoDir = "C:\\Users\\" + getSysUsername_s() + "\\AppData\\LocalLow\\DigitalDiscord\\";

		dirPathExits = true;

	}


#endif //USE_WIN_

#ifdef USE_LINUX_
	std::string getSysUsername_s() {
		return (std::string)getenv("USERNAME");
	}

	std::wstring getSysUsername_w() {
		std::string tmp; 
		tmp.assign(getenv("USERNAME"), strlen(getenv("USERNAME")));

		std::wstring ret(tmp.begin(), tmp.end());

		return ret;
	}

	void createFiles() {

		std::wstring path;
		path += L"~/.config/DigitalDiscord/";

		if (std::experimental::filesystem::exists(path)) {

			if (std::experimental::filesystem::create_directory(path)) {
				throw DirMakeError;
			}
		}
		Setup::pathtoDir_w = path;
		Setup::pathtoDir = "~/.config/DigitalDiscord/";
	}

#endif //USE_LINUX_
	
	/* ---------------------------- comment because we have to fix the include loop ---------------------------
	void resetFiles(bool createAsNew = false) {
		if (pathtoDir == "") {
			InternalErrLog::LogMain.append(time(NULL), "ResetFilesError");
			throw ResetFilesError;
		}
		else {
			std::ofstream ofile;

			InternalEventMap::update();
			if (InternalEventMap::get(Events::FirstRun)) {
				ofile.open(pathtoDir + "DDcord_GenerallDatas.txt", std::ios::trunc | std::ios::beg);		//usermanipulateable

				ofile.write(((std::string)"Username = " + getSysUsername_s().c_str() + "\n").c_str(), 13 + getSysUsername_s().length());
			}
		}
	}
	*/

}


#endif
