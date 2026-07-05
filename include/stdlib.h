/***************************************************
 * FILENAME :    stdlib.h
 * 
 * DESCRIPTION :
 * 
 * AUTHOR :
 */

#ifndef _LIBRAC2_STDLIB_H_
#define _LIBRAC2_STDLIB_H_

#include "types.h"


//--------------------------------------------------------
__LIBRAC2_INLINE__ void* malloc( unsigned long size );
__LIBRAC2_INLINE__ void free( void* ptr );

#endif // _LIBRAC2_STDLIB_H_