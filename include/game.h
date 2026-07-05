#ifndef _LIBRAC2_GAME_H_
#define _LIBRAC2_GAME_H_

#include <tamtypes.h>
#include "types.h"

#ifdef RAC2_PAL
#define Level (*(volatile int*)0x001a7a78)
#define gameModeTimer (*(volatile int*)0x001a8f80)
#define gameMode (*(volatile int*)0x001a8fc0)
#elif RAC2_NTSCJ
#define Level (*(volatile int*)0x001a79f8)
#define gameModeTimer (*(volatile int*)0x001a8f00)
#define gameMode (*(volatile int*)0x001a8f40)
#elif RAC2_NTSCU_V200
#define Level (*(volatile int*)0x001a79f8)
#define gameModeTimer (*(volatile int*)0x001a8f00)
#define gameMode (*(volatile int*)0x001a8f40)
#else
#define Level (*(volatile int*)0x001a79f0)
#define gameModeTimer (*(volatile int*)0x001a8f00)
#define gameMode (*(volatile int*)0x001a8f40)
#endif


#endif // _LIBRAC2_GAME_H_
