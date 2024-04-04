/*
 * parser.h
 *
 *  Created on: Mar 23, 2024
 *      Author: Michał Błotniak
 */
#ifndef INC_PARSER_HPP
#define INC_PARSER_HPP

#include <ring_buffer.h>

#define ENDLINE '\n'

int CheckMessage(RingBuffer_t *Buf);

#endif /*INC_PARSER_HPP*/
