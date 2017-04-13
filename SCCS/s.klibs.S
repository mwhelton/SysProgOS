h41341
s 00025/00000/00000
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
** File:	klibs.S
**
** Author:	Warren R. Carithers and various CSCI-452 sections
**
** Contributor:
**
** Description:	Kernel library assembly-language implementations
*/

#define	__SP_KERNEL__
#define	__SP_ASM__

/*
** _get_ebp - return current contents of EBP at the time of the call
**
** Could be used, e.g., by _kpanic to print a traceback
*/

	.globl	_get_ebp
_get_ebp:
	movl	%ebp, %eax
	ret
E 1
