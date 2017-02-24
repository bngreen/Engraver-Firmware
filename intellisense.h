#pragma once

#if _MSC_VER
#define __IO
#define __weak
#define __attribute__(a)
#define __STATIC_INLINE
#define _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE 1
#define __GNUC__ 1
#define caddr_t int
#define asm(x)
#define register
#undef _WIN32
#endif