/***************************************************
 * FILENAME :		interop.h
 * DESCRIPTION :
 * 		Provides tools to define and reference/invoke addresses in memory by map.
 * NOTES :
 * AUTHOR :			
 */

#ifndef _LIBGC_INTEROP_H_
#define _LIBGC_INTEROP_H_

#include <tamtypes.h>

typedef struct VariableAddress {
	u32 Aranos1;
	u32 Oozla;
	u32 Maktar;
	u32 Endako;
	u32 Barlow;
	u32 Feltzino;
	u32 Notak;
	u32 Siberius;
	u32 Tabora;
	u32 Dobbo;
	u32 Hrugis;
	u32 Joba;
	u32 Todano;
	u32 Boldan;
	u32 Aranos2;
	u32 Gorn;
	u32 Snivelak;
	u32 Smolg;
	u32 Damosel;
	u32 Grelbin;
	u32 Yeedil;
	u32 DobboOrbit;
	u32 DamoselOrbit;
	u32 ShipShack;
	u32 Wupash;
	u32 JammingArray;
	u32 Museum;
} VariableAddress_t;

u32 GetAddress(VariableAddress_t* address);
u32 GetAddressImmediate(VariableAddress_t* address);

#endif // _LIBGC_INTEROP_H_
