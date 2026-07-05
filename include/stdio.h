/***************************************************
 * FILENAME :		stdio.h
 * DESCRIPTION :
 * 		Contains useful functions for debugging.
 * AUTHOR :			
 */

#ifndef _LIBRAC2_STDIO_H_
#define _LIBRAC2_STDIO_H_

#include "types.h"


//--------------------------------------------------------
__LIBRAC2_INLINE__ int sprintf(char * buffer, const char * format, ...);
__LIBRAC2_INLINE__ int snprintf(char * buffer, long n, const char * format, ...);
__LIBRAC2_INLINE__ int printf(const char * format, ...);

__LIBRAC2_INLINE__ int sce_snprintf(char * buffer, long n, const char * format, ...);

//--------------------------------------------------------
#ifdef DEBUG
    #define DPRINTF(fmt, ...)       \
        printf("%s"fmt, "", ##__VA_ARGS__);
#else
    #define DPRINTF(fmt, ...) 
#endif


#endif // _LIBRAC2_STDIO_H_
