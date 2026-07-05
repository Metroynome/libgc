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

typedef enum {
	GAME_MODE_NONE = -2,
	GAME_MODE_DEBUG = -1,
	GAME_MODE_NORMAL = 0,
	GAME_MODE_MOVIE = 1,
	GAME_MODE_SCENE = 2,
	GAME_MODE_PAUSE = 3,
	GAME_MODE_FREEZE = 4,
	GAME_MODE_VENDOR = 5,
	GAME_MODE_SPACE = 6,
	GAME_MODE_PUZZLE = 7,
	GAME_MODE_WEAPON_UPGRADE = 8,
	GAME_MODE_CREDITS = 9,
	GAME_MODE_LOBBY = 10,
	GAME_MODE_FLYBY = 11,
	GAME_MODE_THERMAL = 12,
	GAME_MODE_MAX = 12,
} eGameMode;


#endif // _LIBRAC2_GAME_H_
