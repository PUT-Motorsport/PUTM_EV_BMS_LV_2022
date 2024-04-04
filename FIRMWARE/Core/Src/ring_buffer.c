/*
 * ring_buffer.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Michał Błotniak
 */
#include <ring_buffer.h>
#include "main.h"

//
// Read from Ring Buffer
//
// RingBuffer_t *Buf - pointer to Ring Buffer structure
// uint8_t *Value - pointer to place where a value from buffer is read
//
RB_Status RB_Read(RingBuffer_t *Buf, uint8_t *Value)
{
	// Check if Tail hit Head
	if(Buf->Head == Buf->Tail)
	{
		// If yes - there is nothing to read
		return RB_ERROR;
	}

	// Write current value from buffer to pointer from argument
	*Value = Buf->Buffer[Buf->Tail];

	// Calculate new Tail pointer
	Buf->Tail = (Buf->Tail + 1) % RING_BUFFER_SIZE;

	// Everything is ok - return OK status
	return RB_OK;
}

//
// Write to Ring Buffer
//
// RingBuffer_t *Buf - pointer to Ring Buffer structure
// uint8_t Value - a value to store in the buffer
//
RB_Status RB_Write(RingBuffer_t *Buf, uint8_t Value)
{
	// Calculate new Head pointer value
	uint8_t HeadTmp = (Buf->Head + 1) % RING_BUFFER_SIZE;

	// Check if there is one free space ahead the Head buffer
	if(HeadTmp == Buf->Tail)
	{
		// There is no space in the buffer - return an error
		return RB_ERROR;
	}

	// Store a value into the buffer
	Buf->Buffer[Buf->Head] = Value;

	// Remember a new Head pointer value
	Buf->Head = HeadTmp;

	// Everything is ok - return OK status
	return RB_OK;
}

//
// Free whole Ring Buffer
//
void RB_Clear(RingBuffer_t *Buf)
{
	// Just reset Head and Tail pointers
	Buf->Head = 0;
	Buf->Tail = 0;
}

