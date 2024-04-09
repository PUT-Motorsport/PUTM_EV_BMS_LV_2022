/*
 * ring_buffer.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Michał Błotniak
 */


#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include<stdint.h>
//global definition of the size of all buffers in the library "Ring Buffer"
#define RING_BUFFER_SIZE 16

#ifdef __cplusplus
extern "C" {
#endif

/* -Succes status- */
typedef enum
{
	RB_OK       = 0,
	RB_ERROR	= 1
}RB_Status;

/* -Object Ring Buffer- */

typedef struct
{
	//array of characters
	uint8_t Buffer[RING_BUFFER_SIZE];

	//Head and tail pointers
	uint16_t Head;
	uint16_t Tail;

} RingBuffer_t;

/* -Write- */
//The function writes data to the Buffer
RB_Status RB_Write(RingBuffer_t *Buf, uint8_t Value);


/* -Read- */
//The function reads data from Buffer
RB_Status RB_Read(RingBuffer_t *Buf, uint8_t *Value);


/* -Clear- */
//The function clears the contents of the buffer
void RB_Flush(RingBuffer_t *Buf);

#ifdef __cplusplus
}
#endif

#endif /* INC_RING_BUFFER_H_ */
