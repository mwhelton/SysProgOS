h05073
s 00153/00000/00000
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
** File:	sio.h
**
** Author:	Warren R. Carithers
**
** Contributor:
**
** Description:	SIO definitions
*/

#ifndef _SIO_H_
#define _SIO_H_

/*
** General (C and/or assembly) definitions
*/

// sio interrupt settings

#define	SIO_TX		0x01
#define	SIO_RX		0x02
#define	SIO_BOTH	(SIO_TX | SIO_RX)

#ifndef __SP_ASM__

#include "queue.h"

/*
** Start of C-only definitions
*/

/*
** PUBLIC GLOBAL VARIABLES
*/

// the "blocked for reading" queue

extern queue_t _reading;

/*
** PUBLIC FUNCTIONS
*/

/*
** _sio_init()
**
** Initialize the UART chip.
*/
void _sio_init( void );

/*
** _sio_enable()
**
** enable/disable SIO interrupts
**
** usage:       old = _sio_enable( which )
**
** enables interrupts according to the 'which' parameter
**
** returns the prior settings
*/
uint8_t _sio_enable( uint8_t which );

/*
** _sio_disable()
**
** disable/disable SIO interrupts
**
** usage:       old = _sio_disable( which )
**
** disables interrupts according to the 'which' parameter
**
** returns the prior settings
*/
uint8_t _sio_disable( uint8_t which );

/*
** _sio_input_queue()
**
** get the input queue length
**
** usage:	num = _sio_input_queue()
**
** returns the count of characters still in the input queue
*/
int _sio_input_queue( void );

/*
** _sio_readc()
**
** get the next input character
**
** usage:	ch = _sio_readc()
**
** returns the next character, or -1 if no character is available
*/
int _sio_readc( void );

/*
** _sio_reads()
**
** get an input line, up to a specific number of characters
**
** usage:	num = _sio_reads(buffer,length)
**
** returns the number of characters put into the buffer, or 0 if no
** characters are available
*/
int _sio_reads( char *buffer, int length );

/*
** _sio_writec( ch )
**
** write a character to the serial output
**
** usage:	_sio_writec( ch )
*/
void _sio_writec( int ch );

/*
** _sio_writes( ch )
**
** write a buffer of characters to the serial output
**
** usage:	n = _sio_writes( char *buffer, int length )
**
** returns the count of bytes transferred
*/
int _sio_writes( char *buffer, int length );

/*
** _sio_puts( buf )
**
** write a NUL-terminated buffer of characters to the serial output
**
** usage:	n = _sio_puts( char *buffer );
**
** returns the count of bytes transferred
*/
int _sio_puts( char *buffer );

/*
** _sio_dump()
**
** dump the contents of the SIO buffers
*/
void _sio_dump( void );

#endif

#endif
E 1
