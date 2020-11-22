#ifndef INTERNAL_DEF_H
#define INTERNAL_DEF_H
//defs for files
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS

#include <experimental/filesystem>

//check what OS
#if defined(_WIN32)
#define OS "WINDOWS"
#define USE_WIN_
#endif

#if defined(__linux__)
#define OS "LINUX"
#define USE_LINUX_
#endif

//make fs to std::experimental::filesystem
namespace fs = std::experimental::filesystem;
using filesystemPath = fs::v1::path;


namespace mac {}

#ifdef USE_WIN_
#include <windows.h>
namespace mac {
    void sleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }

    void clearScceen() {
        system("cls");
    }
}
#else //USE_LINUX_
#include <unistd.h>
namespace mac {
    void sleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }

    void clearScceen() {
        system("clear");
    }
}
#endif

#define MY_DEBUG 1

//defs for tools
#define DEBUG_START_ if(MY_DEBUG == 1) {
#define DEBUG_END_ }

//functions
#if MY_DEBUG == 1
#define EXIT_WITH(code) std::cout << "Exited with code: " << code << "\n";
#else
#define EXIT_WITH(code) 
#endif
#endif