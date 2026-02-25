/***************************************************
 * FILENAME :    stdlib.h
 * 
 * DESCRIPTION :
 * 
 * AUTHOR :
 */

#ifndef _LIBGC_STDLIB_H_
#define _LIBGC_STDLIB_H_

#include "types.h"


//--------------------------------------------------------
__LIBGC_INLINE__ void* malloc( unsigned long size );
__LIBGC_INLINE__ void free( void* ptr );

#endif // _LIBGC_STDLIB_H_