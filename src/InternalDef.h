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
    const std::vector<std::string> allStdFiles = {"DD_Cryp.txt", "DD_Config.txt", "IkarusBuild.txt" /* more are comming soon */};
    const std::vector<std::string> allStdDirs = {"xy" /* more are comming soon */};
}

namespace mac { //defs in mac.cpp

    void pause();
    
    void sleep(unsigned milliseconds);

    void tsleep(unsigned milliseconds); 

    void clearScreen();
}

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

//defs for tools
#define DEBUG_START_ if(DEBUG_LEVEL == 1) {
#define DEBUG_END_ }
#define MTRY_BEGIN try {
#define MCATCH(what) } catch(what) {
#define MCATCH_ALL } catch(...) {
#define MCATCH_END }
#define MCATCH_AND_IGNORRE(code) try { code} catch(...) {;}
#define INFINITY_LOOP 1
#define MDEF inline
#define NONE false
#define elif else if
#define VOIDcReturn return IL::c_VOID{};

//Debugging
#if DEBUG_LEVEL == 1 //all
#define EXIT_WITH(code) std::cout << "Exited with code: " << code << "\n";
#define ERROR_MESSAGE(message) std::cout << "[ERROR] " << message << "\n";
#define DEBUG_MESSAGE(message) std::cout << "[DEBUG] " << message << "\n";
#define INFO_MESSAGE(message) std::cout << "[INFO] " << message << "\n";
#define ERROR_IF(statement) if(statement) {ERROR_MESSAGE("ERROR IN ERROR_IF! "); mac::pause();}
#define M_ASSERT(statement) ERROR_IF(!statement)
#define MESSAGE_IF(statement, message) if(statement) {std::cout << "[DEBUG]: " << message << "\n";}
#define THROW_ERROR ERROR_IF(true)
#define DEBUG_WITH_FLUSH(message) std::cout << "[DEBUG] " << message << std::endl;

#elif DEBUG_LEVEL == 2 //only errors
#define ERROR_MESSAGE(message) std::cout << "[ERROR] " << message << "\n";
#define ERROR_IF(statement) if(statement) {ERROR_MESSAGE("ERROR IN ERROR_IF! "); mac::pause();}
#define M_ASSERT(statement) ERROR_IF(!statement)
#define THROW_ERROR ERROR_IF(true)

#elif DEBUG_LEVEL == 3 //only debug
#define DEBUG_MESSAGE(message) std::cout << "[DEBUG] " << message << "\n";
#define MESSAGE_IF(statement, message) if(statement) {std::cout << "[DEBUG]: " << message << "\n";}

#elif DEBUG_LEVEL == 5 //only infos
#define INFO_MESSAGE(message) std::cout << "[INFO] " << message << "\n";

#endif

//def as none if not in any error-level
#ifndef EXIT_WITH
#define EXIT_WITH(code)
#endif
#ifndef ERROR_MESSAGE
#define ERROR_MESSAGE(message)
#endif
#ifndef DEBUG_MESSAGE
#define DEBUG_MESSAGE(message) 
#endif
#ifndef INFO_MESSAGE
#define INFO_MESSAGE(message) 
#endif
#ifndef ERROR_IF
#define ERROR_IF(statement)
#endif
#ifndef M_ASSERT
#define M_ASSERT(statement)
#endif
#ifndef MESSAGE_IF
#define MESSAGE_IF(statement,message)
#endif
#ifndef THROW_ERROR
#define THROW_ERROR
#endif
#ifndef DEBUG_WITH_FLUSH
#define DEBUG_WITH_FLUSH(message)
#endif

#endif //include guard