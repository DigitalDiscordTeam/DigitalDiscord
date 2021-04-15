#include "InternalSys.h"
#include <fstream>

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

		std::wstring tmp(username, size-1);
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

	bool System::checkIfPaths() {
		if (fs::exists("C:\\Users\\" + getSysUsername_s() + "\\AppData\\Roaming\\DigitalDiscord\\")) {
			pathtoDir_w = L"C:\\Users\\" + getSysUsername_w() + L"\\AppData\\Roaming\\DigitalDiscord\\";
			pathtoDir = "C:\\Users\\" + getSysUsername_s() + "\\AppData\\Roaming\\DigitalDiscord\\";
			return true;
		}
		else {
			return false;
		}
	}

	void System::createPath() {
		System::pathtoDir_w = L"C:\\Users\\" + getSysUsername_w() + L"\\AppData\\Roaming\\DigitalDiscord\\";
		System::pathtoDir = "C:\\Users\\" + getSysUsername_s() + "\\AppData\\Roaming\\DigitalDiscord\\";

		if (!fs::exists(pathtoDir)) {
			if (!fs::create_directory(pathtoDir)) {
				throw DirMakeError{};
			}
		}
	}


#endif //USE_WIN_

#ifdef USE_LINUX_
	#include <unistd.h>
	#include <pwd.h>
	std::string System::getSysUsername_s() {
    	uid_t uid = geteuid ();
        passwd *pw = getpwuid (uid);
        if (pw) {
            return std::string(pw->pw_name);
        }
        return "";
    
	}

	std::wstring System::getSysUsername_w() {
		std::string tmp; 
		tmp.assign(getenv("USERNAME"), strlen(getenv("USERNAME")));

		std::wstring ret(tmp.begin(), tmp.end());

		return ret;
	}

	bool System::checkIfPaths() {
		if (fs::exists(L"~/.config/DigitalDiscord/")) {
			pathtoDir_w = L"~/.config/DigitalDiscord/";
			pathtoDir = "~/.config/DigitalDiscord/";
			return true;
		}
		else {
			return false;
		}
	}

	void System::createPath() {

		System::pathtoDir_w = L"~/.config/DigitalDiscord/";
		System::pathtoDir = "~/.config/DigitalDiscord/";

		if (!fs::exists(pathtoDir)) {
			if (!fs::create_directory(pathtoDir)) {
				throw DirMakeError{};
			}
		}
	}

#endif //USE_LINUX_

bool System::doPaths() {
	checkIfPaths();
	if(!checkIfPaths()) {
		createPath();
		System::firstTime = true; //it might be the first time the programm runs on the system
	}
	
	if(fs::current_path().has_filename()) {
		currentPath = fs::current_path().parent_path().string() + ST;
	}
	else {
		currentPath = fs::current_path().string() + ST;
	}

	for(size_t i = 0; i < mac::allStdDirs.size(); ++i) {
		if(!fs::exists(pathtoDir + mac::allStdDirs[i]))
			fs::create_directory(pathtoDir + mac::allStdDirs[i]);
	}
	std::ofstream ofile;
	for(size_t i = 0; i < mac::allStdFiles.size(); ++i) {
		ofile.open(pathtoDir + mac::allStdFiles[i]);
		ofile.close();
	}

	return firstTime;
}