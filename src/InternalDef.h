#ifndef INTERNAL_DEF_H
#define INTERNAL_DEF_H

//defs for files
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS
#define _UNICODE
#define UNICODE

#include <filesystem>
#include <iostream>
#include <vector>

//check witch OS
#if defined(_WIN32)
#define ST "\\"
#define OS "WINDOWS"
#define USE_WIN_
#endif

#if defined(__linux__)
#define ST "/"
#define OS "LINUX"
#define USE_LINUX_
#endif

namespace fs = std::filesystem;
using filesystemPath = fs::path;
using tokenType = std::vector<std::string>;

namespace mac {
    const std::vector<std::string> allStdFiles = {"VERSION.txt"};
    const std::vector<std::string> allStdDirs = {"Manuals", "Hubs"};

/// Current paths:
///             Windows:
///
///             C:
///             Users
///             <Username>
///             %APPDATA%
///             Roaming
///             DigitalDiscord
///
///
///             Linux:
///             home
///             <Username>
///             .config
///             DigitalDiscord
///

}

namespace mac { //defines in mac.cpp
    inline int debuglevel = 0;
    void pause();
    
    void sleep(unsigned milliseconds);

    void tsleep(unsigned milliseconds); 

    void clearScreen();
}

#define MDEF inline
#define NONE false
#define VOIDcReturn return IL::c_VOID{};
#define STATIC_MASSERT(statement) if(!(statement)) {std::cout << "[STATIC_ASSERT] FAILED AT: " << #statement << "\n"; mac::pause(); }

//Debugging
#define ENABLE_DEBUG(val) mac::debuglevel = val;
#define STOP_DEBUG  mac::debuglevel = 0;
#define EXIT_WITH(code) std::cout << "Exited with code: " << code << "\n";
#define ERROR_MESSAGE(message) if(mac::debuglevel==1 || mac::debuglevel == 3) {std::cout << "[ERROR] "  << message << "\n";}
#define DEBUG_MESSAGE(message) if(mac::debuglevel==1 || mac::debuglevel == 2) {std::cout << "[DEBUG] "  << message << "\n";}
#define INFO_MESSAGE(message)  if(mac::debuglevel==1 || mac::debuglevel == 4) {std::cout << "[INFO] "  << message << "\n";}
#define ERROR_IF(statement) if(statement) {ERROR_MESSAGE("ERROR IN ERROR_IF! [ " << #statement << " ]"); mac::pause();}
#define M_ASSERT(statement) ERROR_IF(!statement)
#define MESSAGE_IF(statement, message) if(statement) {std::cout << "[DEBUG]: " << message << "\n";}
#define THROW_ERROR ERROR_IF(true)
#define DEBUG_WITH_FLUSH(message) std::cout << "[DEBUG] " << message << std::endl;


#endif //include guard