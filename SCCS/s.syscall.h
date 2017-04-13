h28943
s 00079/00000/00000
d D 1.1 17/04/13 13:16:37 wrc 1 0
c date and time created 17/04/13 13:16:37 by wrc
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
** File:	syscall.h
**
** Author:	CSCI-452 class of 20165
**
** Contributor:
**
** Description:	system call module declarations
*/

#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include "common.h"

/*
** General (C and/or assembly) definitions
*/

// system call codes

#define	SYS_exit	0
#define	SYS_read	1
#define	SYS_write	2
#define	SYS_fork	3
#define	SYS_exec	4
#define	SYS_kill	5
#define	SYS_wait	6
#define	SYS_sleep	7
#define	SYS_getpid	8
#define	SYS_getppid	9
#define	SYS_gettime	10
#define	SYS_getstatus	11

#define	N_SYSCALLS	12

// dummy system call code to test the ISR

#define	SYS_bogus	(N_SYSCALLS + 100)

// system call interrupt vector number

#define	INT_VEC_SYSCALL	0x80

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

extern queue_t _zombie;		// the living dead
extern queue_t _waiting;	// concerned parents

/*
** Prototypes
*/

/*
** _sys_init()
**
** initializes all syscall-related data structures
*/
void _sys_init( void );

// that's all - everything else is not callable from elsewhere!

#endif

#endif
E 1
