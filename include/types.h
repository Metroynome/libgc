#ifndef _LIBRAC2_TYPES_H_
#define _LIBRAC2_TYPES_H_

#include <tamtypes.h>


#if (defined(GC_PAL_V100) || defined(GC_NTSCU_V100) || defined(GC_NTSCJ_V100)) && !defined(GC_V100)
#define GC_V100
#endif

#if (defined(GC_PAL_V200) || defined(GC_NTSCU_V200) || defined(GC_NTSCJ_V200)) && !defined(GC_V200)
#define GC_V200
#endif

#if (defined(RAC2_PAL_V100) || defined(RAC2_NTSCU_V100) || defined(RAC2_NTSCJ_V100)) && !defined(RAC2_V100)
#define RAC2_V100
#endif

#if (defined(RAC2_PAL_V200) || defined(RAC2_NTSCU_V200) || defined(RAC2_NTSCJ_V200)) && !defined(RAC2_V200)
#define RAC2_V200
#endif

#if (defined(GC_PAL) || defined(GC_NTSCU) || defined(GC_NTSCJ)) && !defined(GC_V100) && !defined(GC_V200)
#define GC_V100
#endif

#if (defined(RAC2_PAL) || defined(RAC2_NTSCU) || defined(RAC2_NTSCJ)) && !defined(RAC2_V100) && !defined(RAC2_V200)
#define RAC2_V100
#endif

#if defined(GC_V100) && !defined(RAC2_V100)
#define RAC2_V100
#endif

#if defined(GC_V200) && !defined(RAC2_V200)
#define RAC2_V200
#endif

#if defined(RAC2_V100) && !defined(GC_V100)
#define GC_V100
#endif

#if defined(RAC2_V200) && !defined(GC_V200)
#define GC_V200
#endif

#if defined(GC_PAL_V100) && !defined(GC_PAL)
#define GC_PAL
#endif

#if defined(GC_NTSCU_V100) && !defined(GC_NTSCU)
#define GC_NTSCU
#endif

#if defined(GC_NTSCJ_V100) && !defined(GC_NTSCJ)
#define GC_NTSCJ
#endif

#if defined(GC_PAL_V200) && !defined(GC_PAL)
#define GC_PAL
#endif

#if defined(GC_NTSCU_V200) && !defined(GC_NTSCU)
#define GC_NTSCU
#endif

#if defined(GC_NTSCJ_V200) && !defined(GC_NTSCJ)
#define GC_NTSCJ
#endif

#if defined(RAC2_PAL_V100) && !defined(RAC2_PAL)
#define RAC2_PAL
#endif

#if defined(RAC2_NTSCU_V100) && !defined(RAC2_NTSCU)
#define RAC2_NTSCU
#endif

#if defined(RAC2_NTSCJ_V100) && !defined(RAC2_NTSCJ)
#define RAC2_NTSCJ
#endif

#if defined(RAC2_PAL_V200) && !defined(RAC2_PAL)
#define RAC2_PAL
#endif

#if defined(RAC2_NTSCU_V200) && !defined(RAC2_NTSCU)
#define RAC2_NTSCU
#endif

#if defined(RAC2_NTSCJ_V200) && !defined(RAC2_NTSCJ)
#define RAC2_NTSCJ
#endif

#if defined(GC_PAL) && !defined(RAC2_PAL)
#define RAC2_PAL
#endif

#if defined(GC_NTSCU) && !defined(RAC2_NTSCU)
#define RAC2_NTSCU
#endif

#if defined(GC_NTSCJ) && !defined(RAC2_NTSCJ)
#define RAC2_NTSCJ
#endif

#if defined(RAC2_PAL) && !defined(GC_PAL)
#define GC_PAL
#endif

#if defined(RAC2_NTSCU) && !defined(GC_NTSCU)
#define GC_NTSCU
#endif

#if defined(RAC2_NTSCJ) && !defined(GC_NTSCJ)
#define GC_NTSCJ
#endif

#if defined(GC_PAL) && defined(GC_V100) && !defined(GC_PAL_V100)
#define GC_PAL_V100
#endif

#if defined(GC_NTSCU) && defined(GC_V100) && !defined(GC_NTSCU_V100)
#define GC_NTSCU_V100
#endif

#if defined(GC_NTSCJ) && defined(GC_V100) && !defined(GC_NTSCJ_V100)
#define GC_NTSCJ_V100
#endif

#if defined(GC_PAL) && defined(GC_V200) && !defined(GC_PAL_V200)
#define GC_PAL_V200
#endif

#if defined(GC_NTSCU) && defined(GC_V200) && !defined(GC_NTSCU_V200)
#define GC_NTSCU_V200
#endif

#if defined(GC_NTSCJ) && defined(GC_V200) && !defined(GC_NTSCJ_V200)
#define GC_NTSCJ_V200
#endif

#if defined(RAC2_PAL) && defined(RAC2_V100) && !defined(RAC2_PAL_V100)
#define RAC2_PAL_V100
#endif

#if defined(RAC2_NTSCU) && defined(RAC2_V100) && !defined(RAC2_NTSCU_V100)
#define RAC2_NTSCU_V100
#endif

#if defined(RAC2_NTSCJ) && defined(RAC2_V100) && !defined(RAC2_NTSCJ_V100)
#define RAC2_NTSCJ_V100
#endif

#if defined(RAC2_PAL) && defined(RAC2_V200) && !defined(RAC2_PAL_V200)
#define RAC2_PAL_V200
#endif

#if defined(RAC2_NTSCU) && defined(RAC2_V200) && !defined(RAC2_NTSCU_V200)
#define RAC2_NTSCU_V200
#endif

#if defined(RAC2_NTSCJ) && defined(RAC2_V200) && !defined(RAC2_NTSCJ_V200)
#define RAC2_NTSCJ_V200
#endif


#define __LIBRAC2_GETTER__    inline
#define __LIBRAC2_SETTER__    inline
#define __LIBRAC2_INLINE__    inline


#define true 1
#define false 0
typedef _Bool bool;

#endif
