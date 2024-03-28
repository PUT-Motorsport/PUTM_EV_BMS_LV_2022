/*
 * parser.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Michał Błotniak
 */




#include "main.h"
#include "ring_buffer.h"
#include "parser.h"
#include "string.h"
#include <usbd_cdc_if.h>

int CheckMessage(RingBuffer_t *Buf) {
    static uint8_t lineBuffer[20];  // Buffer for text lines, adjust size as needed
    static uint8_t lineIndex = 0;   // used to write subsequent bytes of data.
    uint8_t tmpByte;                //Temporary byte storage

    while(RB_Read(Buf, &tmpByte) == RB_OK) {
        if(tmpByte == ENDLINE) {
            lineBuffer[lineIndex] = '\0';
            lineIndex = 0;

            // Check if the line contains "BB_Start"
            if(strcmp((char*)lineBuffer, "BB_Start") == 0) {
                return 1; // Znaleziono ciąg znaków
            }
        } else {
        	// Build lines of text
            if(lineIndex < sizeof(lineBuffer) - 1) {
                lineBuffer[lineIndex++] = tmpByte;
            }
        }
    }

    return 0; // "BB_Start" not found
}

