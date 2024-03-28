/*
 * parser.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Michał Błotniak
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "ring_buffer.h"

#define ENDLINE '\n'

int CheckMessage(RingBuffer_t *Buf);

#ifdef __cplusplus
}
#endif
