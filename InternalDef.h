#ifndef INTERNAL_DEF_H
#define INTERNAL_DEF_H
//defs for files
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS
#define _UNICODE
#define UNICODE

#include <filesystem>
#include <iostream>

//check witch OS
#if defined(_WIN32)
#define OS "WINDOWS"
#define USE_WIN_
#endif

#if defined(__linux__)
#define OS "LINUX"
#define USE_LINUX_
#endif

namespace fs = std::filesystem;
using filesystemPath = fs::path;
using tokenType = std::vector<std::string>;

namespace mac {
    void pause() {
        std::cout << "Please press any button...";
        if(!getchar() == '\n') {
            std::cout << "\n";
        }
    }
}

#ifdef USE_WIN_
#include <windows.h>
namespace mac {
    void sleep(unsigned milliseconds) {
        Sleep(milliseconds);
    }

    void clearScreen() {
        system("cls");
    }
}
#elif defined(USE_LINUX_)
#include <unistd.h>
namespace mac {
    void sleep(unsigned milliseconds) {
        usleep(milliseconds * 1000); // takes microseconds
    }

    void clearSrceen() {
        system("clear");
    }
}
#else // USE_UNKNOWN_
namespace mac {
    void sleep(unsigned milliseconds) {
        
    }

    void clearScceen() {
        
    }
}
#endif

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
#define INFINITY_LOOP 1

//Debugging
#if DEBUG_LEVEL == 1
#define EXIT_WITH(code) std::cout << "Exited with code: " << code << "\n";
#define ERROR_MESSAGE(message) std::cout << "[ERROR] " << message << "\n";
#define DEBUG_MESSAGE(message) std::cout << "[DEBUG] " << message << "\n";
#define INFO_MESSAGE(message) std::cout << "[INFO] " << message << "\n";
#define ERROR_IF(statement) if(statement) {ERROR_MESSAGE("ERROR IN ERROR_IF! "); mac::pause();}
#define M_ASSERT(statement) ERROR_IF(statement)
#define MESSAGE_IF(statement, message) if(statement) {std::cout << "[DEBUG]: " << message << "\n";}
#define THROW_ERROR ERROR_IF(true)
#else
#define EXIT_WITH(code)
#define ERROR_MESSAGE(message)
#define DEBUG_MESSAGE(message)
#define INFO_MESSAGE(message) 
#define ERROR_IF(statement) 
#define M_ASSERT(statement)
#define MESSAGE_IF(statement,message)
#define THROW_ERROR
#endif

#endif //include guard