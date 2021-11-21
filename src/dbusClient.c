/******************************************************************************
* @file    dbusClient.c
* @brief   
******************************************************************************/

#include <stdlib.h>
#include "dbusClient.h"

int signalCallback(sd_bus_message *msg, void *userdata, sd_bus_error *retError)
{
    uint8_t * pReceivedArray;
    size_t    receivedArrayLength;

    /* Read the message */
    (void)sd_bus_message_read_array(msg, 'y',  (const void**) &pReceivedArray,
    &receivedArrayLength);
    printf("Signal 1 was received on Object B, byte array with length: %li and "
    "first four bytes: %x%x%x%x was received\n", receivedArrayLength, pReceivedArray[0],
    pReceivedArray[1], pReceivedArray[2], pReceivedArray[3]);

    /* sd-bus expects the callback to return a positive integer */
    return 1;
}