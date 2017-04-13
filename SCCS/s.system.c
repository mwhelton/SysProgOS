h02611
s 00257/00000/00000
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
** File:	system.c
**
** Author:	Warren R. Carithers and various CSCI-452 classes
**
** Contributor:
**
** Description:	miscellaneous OS support functions
*/

#define	__SP_KERNEL__

#include "common.h"

#include "common.h"

#include "system.h"
#include "clock.h"
#include "process.h"
#include "bootstrap.h"
#include "syscall.h"
#include "sio.h"
#include "scheduler.h"

// need init() address
#include "user.h"

// need the exit() and do_exit() prototypes
#include "ulib.h"

/*
** PRIVATE DEFINITIONS
*/

/*
** PRIVATE DATA TYPES
*/

/*
** PRIVATE GLOBAL VARIABLES
*/

/*
** PUBLIC GLOBAL VARIABLES
*/

/*
** PRIVATE FUNCTIONS
*/

/*
** PUBLIC FUNCTIONS
*/

/*
** _zombify(pcb)
**
** turn a process into a zombie, or give its status to
** a waiting parent
*/
void _zombify( pcb_t *pcb ) {

	// sanity check!
	if( pcb == NULL ) {
		_kpanic( "_zombify", "NULL pcb parameter" );
	}

	// reparent any children this process has

	if( pcb->children > 0 ) {
		pcb_t *whom;
		whom = _pcb_find_child_of( pcb->pid );
		while( whom != NULL ) {
			whom->ppid = PID_INIT;
			_init_pcb->children += 1;
			whom = _pcb_find_child_of( -1 );
		}
		pcb->children = 0;
	}
	
	// add to zombie queue
	// what if parent is already wait()ing?
	// 	deal with the child directly
	pcb_t *parent = _pcb_find( pcb->ppid );
	if( parent == NULL ) {
		c_printf( "*** _zombify: want parent %d for %d\n",
			  pcb->ppid, pcb->pid );
		_kpanic( "_zombify", "parent process doesn't exist!" );
	}
	
	if( parent->state == PS_WAITING ) {

		// pull the parent from the wait queue
		status_t status = _q_remove( &_waiting, (void *) parent );
		if( status != E_SUCCESS ) {
			c_printf( "*** _zombify: want parent %d for %d\n",
				  pcb->ppid, pcb->pid );
			_kpanic( "_zombify", "waiting parent isn't???" );
		}

		// success - return info to the parent
		RET(parent) = E_SUCCESS;
		pid_t *arg = (pid_t *) ARG(parent,1);
		*arg = pcb->pid;
		int32_t *stat = (int32_t *) ARG(parent,2);
		*stat = pcb->exitstatus;

		// clean up the child
		_pcb_cleanup( pcb );

		// put the parent back in the ready queue
		_schedule( parent );

	} else {

		// add the child to the zombie horde
		status_t status = _q_enque( &_zombie, (void *) pcb );
		if( status != E_SUCCESS ) {
			_kpanic( "_zombify", "enque zombie failed" );
		}
	}
	
	// do NOT want to dispatch here!
	// whoever called us must do this!
	// _dispatch();  // 20170404
}

/*
** _init - system initialization routine
**
** Called by the startup code immediately before returning into the
** first user process.
*/
void _init( void ) {
	pcb_t *pcb;

	/*
	** BOILERPLATE CODE - taken from basic framework
	**
	** Initialize interrupt stuff.
	*/

	__init_interrupts();	// IDT and PIC initialization

	/*
	** Console I/O system.
	*/

	c_io_init();
	c_setscroll( 0, 7, 99, 99 );
	c_puts_at( 0, 6, "================================================================================" );

	/*
	** 20165-SPECIFIC CODE STARTS HERE
	*/

	/*
	** Initialize various OS modules
	**
	** Note:  the clock, SIO, and syscall modules also install
	** their ISRs.
	*/

	c_puts( "System initialization starting\n" );
	c_puts( "------------------------------\n" );
//	__delay( 200 );  // about 5 seconds

	c_puts( "Module init: " );

	_q_init();		// must be first
	_pcb_init();		// processes
	_stk_init();		// stacks
	_sched_init();		// scheduler
	_sio_init();		// serial i/o
	_sys_init();		// syscalls
	_clk_init();		// clock

	c_puts( "\nModule initialization complete\n" );
	c_puts( "------------------------------\n" );

	/*
	** Create the initial system ESP
	**
	** This will be the address of the next-to-last
	** longword in the system stack.
	*/

	_system_esp = ((uint32_t *) ( (&_system_stack) + 1)) - 2;

	/*
	** Create the initial process
	**
	** Code largely stolen from _sys_fork() and _sys_exec(); if
	** either or both of those routines change, SO MUST THIS!!!
	*/

	// allocate a PCB and stack

	pcb = _pcb_alloc();
	if( pcb == NULL ) {
		_kpanic( "_init", "init() pcb alloc failed" );
	}

	pcb->stack = _stk_alloc();
	if( pcb->stack == NULL ) {
		_kpanic( "_init", "init() stack alloc failed" );
	}

	// initialize the stack with the standard context

	pcb->context = _stk_setup( pcb->stack, (uint32_t) init, 0 );
	if( pcb->context == NULL ) {
		_kpanic( "_init", "init() stack setup failed" );
	}

	// set up various PCB fields
	pcb->pid = pcb->ppid = PID_INIT;
	pcb->prio = P_SYSTEM;
	pcb->q_default = QUANT_STD;

	// remember it
	_init_pcb = pcb;

	// put it on the ready queue
	_schedule( pcb );

	/*
	** Create the idle() process
	**
	** Philosophical question: should we create it here, or
	** should we let init() create it?
	**
	** We opt for the latter, as it means less work for us. :-)
	*/

	/*
	** Turn on the SIO receiver (the transmitter will be turned
	** on/off as characters are being sent)
	*/

	_sio_enable( SIO_RX );

	// dispatch the first user process

	_dispatch();

	/*
	** END OF 20165-SPECIFIC CODE
	**
	** Finally, report that we're all done.
	*/

	c_puts( "System initialization complete.\n" );
	c_puts( "-------------------------------\n" );
}
E 1
