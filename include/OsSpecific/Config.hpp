#pragma once

#if defined (_WIN32)
#define SG_OS_WINDOWS
#elif defined(__linux__)
#define SG_OS_LINUX
#elif defined(__APPLE__)
#define SG_OS_APPLE
#else
#define SG_OS_UNKNOWN
#endif