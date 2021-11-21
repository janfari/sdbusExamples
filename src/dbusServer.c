/******************************************************************************
* @file    dbusClient.c
* @brief
******************************************************************************/

#include <stdlib.h>
#include "dbusServer.h"
#include "dbusClient.h"
#include "dbus.h"


/**
 * @brief      Message handler for Object A Method 1. Example for strings and ints
 * @note       In order for the function to work without causing dbus errors,
 *             the signature and return sent in sd_bus_reply_method_return
 *             must correspond to what is defined in the vtable
 * @param[in]  pMsg - the incoming message
 * @param[in]  pUserdata - data defined internally to be passed to the handler (unused)
 * @param[out] pRetError - D-Bus error to be passed back (unused)
 * @return     error code from D-Bus calls
 */
int method1Handler(sd_bus_message *pMsg, void *pUserdata, sd_bus_error *pRetError)
{
    int sdbusErr = 0;
    int receivedInt = 0;
    const char* receivedStr = NULL;

    /* Read the D-Bus message */
    sdbusErr = sd_bus_message_read(pMsg, "si", &receivedStr, &receivedInt);
    if (0 > sdbusErr)
    {
        printf("D-Bus Error: Failed to read message: %s\n", strerror(-sdbusErr));
    }
    else
    {
        printf("Method 1 on Object A was called, string: %s and int: %i were received\n",
        receivedStr, receivedInt);
    }

    /* Send various int types and a string as the reply */
    sd_bus_reply_method_return(pMsg, "uxqs", 1, 2, 3, "a string");

    return sdbusErr;
}

/**
 * @brief      Message handler for Object A Method 2. Empty method to trigger signal
 * @note       This is not typical usage, normally a signal would be triggered from
 *             elsewhere in the code. This method is included to easily trigger a signal
 *             from d-feet as an example.
 * @param[in]  pMsg - the incoming message (unused)
 * @param[in]  pUserdata - data defined internally to be passed to the handler (unused)
 * @param[out] pRetError - D-Bus error to be passed back (unused)
 * @return     error code from D-Bus calls
 */
int sendSignal1(sd_bus_message *pMsg, void *pUserdata, sd_bus_error *pRetError)
{
    int sdbusErr = 0;
    uint8_t byteArray[4] = {0xab, 0xcd, 0x12, 0x34};
    sd_bus_message * pOutMessage = NULL;

    /* We have to reply even though it's empty */
    sd_bus_reply_method_return(pMsg, "");

    /* Emit a signal. Usually this would go to another service (kind of silly to send a
     signal to yourself) but we are listening to ourselves in ObjB for ease of example.
     Arrays are a little fussy in dbus afaik you can't use them directly in
     sd_bus_emit_signal, sending an array can be done in three parts like this: */
    sdbusErr = sd_bus_message_new_signal(pBus,
                                  &pOutMessage,
                                  objA_objectPath,    /* Signal emitter path */
                                  objA_interfaceName, /* Signal emitter interface */
                                  "Signal1");         /* Signal name */
    sdbusErr = sd_bus_message_append_array(pOutMessage, 'y', byteArray, sizeof(byteArray));
    sdbusErr = sd_bus_send(pBus, pOutMessage, NULL);

    /* Adding each element individually is also possible though impractical, like this:*/
    sdbusErr = sd_bus_emit_signal(pBus,
                                  objA_objectPath,    /* Signal emitter path */
                                  objA_interfaceName, /* Signal emitter interface */
                                  "Signal1",          /* Signal name */
                                  "ay",
                                  5,                           /* Length of array */
                                  0x00, 0x11, 0x22, 0x33, 0x44 /* Array bytes */
                                  );

    printf("Method 2 on Object A was called, Signal 1 emitted\n");

    return sdbusErr;
}