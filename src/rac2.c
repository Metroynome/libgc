#include "rac2.h"
#include "player.h"

// 
extern void padUpdate(void);
extern void playerPadUpdate(void);

/*
 * NAME :		rac2PreUpdate
 * DESCRIPTION :
 * 			Must be called at the beginning of each tick.
 * NOTES :
 * ARGS : 
 * RETURN :
 * AUTHOR :
 */
void rac2PreUpdate(void)
{
		
}

/*
 * NAME :		rac2PostUpdate
 * DESCRIPTION :
 * 			Must be called at the end of each tick.
 * NOTES :
 * ARGS : 
 * RETURN :
 * AUTHOR :
 */
void rac2PostUpdate(void)
{
	padUpdate();
	playerPadUpdate();
}