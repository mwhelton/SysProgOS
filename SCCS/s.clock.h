h51242
s 00055/00000/00000
d D 1.1 17/04/13 13:16:36 wrc 1 0
c date and time created 17/04/13 13:16:36 by wrc
e
u
U
f e 0
t
T
I 1
/*
** SCCS ID:	%W%	%G%
**
** File:	clock.h
**
** Author:	CSCI-452 class of 20165
**
** Contributor:
**
** Description:	Clock module declarations
*/

#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "common.h"

/*
** General (C and/or assembly) definitions
*/

// standard process quantum (in ticks)

#define	QUANT_STD		5

#ifndef __SP_ASM__

/*
** Start of C-only definitions
*/

/*
** Types
*/

/*
** Globals
*/

extern uint32_t _now;   // the current system time

/*
** Prototypes
*/

/*
** _clk_init()
**
** initialize the clock module
*/
void _clk_init( void );

#endif

#endif
E 1
