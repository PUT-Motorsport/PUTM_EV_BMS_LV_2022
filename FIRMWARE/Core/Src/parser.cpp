/*
 * parser.c
 *
 *  Created on: Mar 23, 2024
 *      Author: Michał Błotniak
 */




#include <global_variables.hpp>
#include <parser.hpp>
#include <ring_buffer.h>
#include "string.h"
#include <usbd_cdc_if.h>

// Function to check if the ring buffer contains "BB_Start" or "BB_Stop"
// Returns 1 for "BB_Start", 0 for "BB_Stop", or -1 if neither of these strings are found
int CheckMessage(RingBuffer_t *Buf) {
    char command[9]; // Sized to fit "BB_Start\0" or "BB_Stop\0"
    uint8_t index = 0;
    uint8_t value;

    // Read bytes from the buffer until a command is assembled or the buffer is exhausted
    while (RB_Read(Buf, &value) == RB_OK) {
        // Check if we've reached the end of a command ('\0' or '\n')
        if (value == '\0' || value == '\n') {
            break;
        }
        // Ensure we do not exceed the command buffer size
        if (index < sizeof(command) - 1) {
            command[index++] = value;
        } else {
            // Too much data for one command, something went wrong
            return -1;
        }
    }
    command[index] = '\0'; // Null-terminate the string

    // Compare the assembled command
    if (strcmp(command, "BB_Start") == 0)
    {
    	data.charging.balance_on = true;
        return 1;
    }
    else if (strcmp(command, "BB_Stop") == 0)
    {
    	data.charging.balance_on = false;
        return 0;
    }
    else if (strcmp(command, "ED_ON") == 0)
    {
    	data.ErrorDetection = true;
    	return 0;
    }
    else if (strcmp(command, "ED_OFF") == 0)
    {
    	data.ErrorDetection = false;
        return 0;
    }

    return -1;
}
