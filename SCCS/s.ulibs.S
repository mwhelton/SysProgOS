h39675
s 00068/00000/00000
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
** File:	ulibs.S
**
** Author:	CSCI-452 class of 20165
**
** Contributor:
**
** Description:	assembly-language user-level library functions
*/

#define	__SP_ASM__

#include "syscall.h"

/*
** System call stubs
**
** All have the same structure:
**
**      move a code into EAX
**      generate the interrupt
**      return to the caller
**
** As these are simple "leaf" routines, we don't use
** the standard enter/leave method to set up a stack
** frame - that takes time, and we don't really need it.
*/

#define	SYSCALL(name) \
	.globl	name			; \
name:					; \
	movl	$SYS_##name, %eax	; \
	int	$INT_VEC_SYSCALL	; \
	ret

SYSCALL(exit)
SYSCALL(read)
SYSCALL(write)
SYSCALL(fork)
SYSCALL(exec)
SYSCALL(kill)
SYSCALL(wait)
SYSCALL(sleep)
SYSCALL(getpid)
SYSCALL(getppid)
SYSCALL(gettime)
SYSCALL(getstatus)

/*
** This is a bogus system call; it's here so that we can test
** our handling of out-of-range syscall codes in the syscall ISR.
*/

SYSCALL(bogus)

/*
** do_exit()
**
** support function used as the "return to" address
** for user main() routines; it just calls exit(%eax)
*/

	.globl  do_exit
do_exit:
	pushl   %eax    // use whatever was in EAX as the status
	call    exit    // terminate this process
E 1
