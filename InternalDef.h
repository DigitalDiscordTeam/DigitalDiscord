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

#endif
