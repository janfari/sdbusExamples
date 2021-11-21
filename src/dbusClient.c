/******************************************************************************
* @file    dbusClient.c
* @brief
******************************************************************************/

#include <stdlib.h>
#include "dbusClient.h"


/**
 * @brief      Callback triggered by Signal 1
 * @note       We subscribe to signal 1 in main.c
 * @param[in]  pMsg - the incoming message
 * @param[in]  pUserdata - data defined internally to be passed to the handler (unused)
 * @param[out] pRetError - D-Bus error to be passed back
 * @return     error code from D-Bus calls
 */
int signalCallback(sd_bus_message *pMsg, void *pUserdata, sd_bus_error *pRetError)
{
    uint8_t * pReceivedArray;
    size_t    receivedArrayLength;

    /* Read the message */
    (void)sd_bus_message_read_array(pMsg, 'y',  (const void**) &pReceivedArray,
    &receivedArrayLength);
    printf("Signal 1 was received on Object B, byte array with length: %li and "
    "first four bytes: %x%x%x%x was received\n", receivedArrayLength, pReceivedArray[0],
    pReceivedArray[1], pReceivedArray[2], pReceivedArray[3]);

    /* sd-bus expects the callback to return a positive integer */
    return 1;
}