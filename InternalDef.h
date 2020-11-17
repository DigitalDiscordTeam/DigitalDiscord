#ifndef INTERNAL_DEF_H
#define INTERNAL_DEF_H

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#define _CRT_SECURE_NO_WARNINGS

#if defined(_WIN32)
#define OS "WINDOWS"
#define USE_WIN_
#endif

#if defined(__linux__)
#define OS "LINUX"
#define USE_LINUX_
#endif

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

#endif