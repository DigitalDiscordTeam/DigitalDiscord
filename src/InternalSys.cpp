#include "InternalSys.h"

std::wstring System::string2wsstring(const std::string& str) {
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.from_bytes(str);
}

std::string System::wstring2string(const std::wstring& wstr) {
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(wstr);
}

#ifdef USE_WIN_

	std::string System::getSysUsername_s() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);

		std::wstring tmp(username, size); //TODO: fix length of name
		std::string ret = System::wstring2string(tmp);
		return ret;
	}

	std::wstring System::getSysUsername_w() {
		TCHAR username[UNLEN + 1];
		DWORD size = UNLEN + 1;
		GetUserName((TCHAR*)username, &size);
		std::wstring tmp(username,size);
		return tmp;
	}

	void System::checkIfPaths() {
		if (fs::exists(L"C:\\Users\\" + getSysUsername_w() + L"\\AppData\\LocalLow\\DigitalDiscord\\")) {
			dirPathExits = true;
			pathtoDir_w = L"C:\\Users\\" + getSysUsername_w() + L"\\AppData\\LocalLow\\DigitalDiscord\\";
			pathtoDir = "C:\\Users\\" + getSysUsername_s() + "\\AppData\\LocalLow\\DigitalDiscord\\";
		}
		else {
			dirPathExits = false;
		}
	}

	void System::createPath() {

		std::wstring path;
		path += L"C:\\Users\\";
		path += getSysUsername_w();
		path += L"\\AppData\\LocalLow\\DigitalDiscord\\";

		System::pathtoDir_w = path;
		System::pathtoDir = "C:\\Users\\" + getSysUsername_s() + "\\AppData\\LocalLow\\DigitalDiscord\\";

		if (!fs::exists(path)) {
			if (!fs::create_directory(path)) {
				throw DirMakeError{};
			}
			for(size_t i = 0; i < mac::allStdDirs.size(); ++i) {
				if(fs::create_directory(pathtoDir + mac::allStdDirs[i])) {
					throw DirMakeError{};
				}
			}
		}

		dirPathExits = true;
	}


#endif //USE_WIN_

#ifdef USE_LINUX_
	std::string System::getSysUsername_s() {
		return (std::string)getenv("USERNAME");
	}

	std::wstring System::getSysUsername_w() {
		std::string tmp; 
		tmp.assign(getenv("USERNAME"), strlen(getenv("USERNAME")));

		std::wstring ret(tmp.begin(), tmp.end());

		return ret;
	}

	void System::checkIfPaths() {
		if (fs::exists(L"~/.config/DigitalDiscord/")) {
			dirPathExits = true;
			pathtoDir_w = L"~/.config/DigitalDiscord/";
			pathtoDir = "~/.config/DigitalDiscord/";
		}
		else {
			dirPathExits = false;
		}
	}

	void System::createPath() {

		std::wstring path;
		path += L"~/.config/DigitalDiscord/";

		System::pathtoDir_w = path;
		System::pathtoDir = "~/.config/DigitalDiscord/";

		if (!fs::exists(path)) {
			if (!fs::create_directory(path)) {
				throw DirMakeError{};
			}
			for(size_t i = 0; i < mac::allStdDirs.size(); ++i) {
				if(fs::create_directory(pathtoDir + mac::allStdDirs[i])) {
					throw DirMakeError{};
				}
			}
		}
	}

#endif //USE_LINUX_

bool System::doPaths() {
	checkIfPaths();
	if(!dirPathExits) {
		createPath();
		System::firstTime = true; //it might be the first time the programm run on the system
	}
	
	if(fs::current_path().has_filename()) {
		currentPath = fs::current_path().parent_path().string() + ST;
	}
	else {
		currentPath = fs::current_path().string() + ST;
	}

	return firstTime;
}