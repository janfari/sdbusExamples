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
 * @param[in]  msg - the incoming message
 * @param[in]  userdata - data defined internally to be passed to the handler (unused)
 * @param[out] retError - D-Bus error to be passed back (unused)
 * @return     error code from D-Bus calls
 */
int method1Handler(sd_bus_message *msg, void *userdata, sd_bus_error *retError)
{
    int sdbusErr = 0;
    int receivedInt = 0;
    const char* receivedStr = NULL;

    /* Read the D-Bus message */
    sdbusErr = sd_bus_message_read(msg, "si", &receivedStr, &receivedInt);
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
    sd_bus_reply_method_return(msg, "uxqs", 1, 2, 3, "a string");

    return sdbusErr;
}

/**
 * @brief      Message handler for Object A Method 2. Empty method to trigger signal
 * @note       This is not typical usage, normally a signal would be triggered from
 *             elsewhere in the code. This method is included to easily trigger a signal
 *             from d-feet as an example.
 * @param[in]  msg - the incoming message (unused)
 * @param[in]  userdata - data defined internally to be passed to the handler (unused)
 * @param[out] retError - D-Bus error to be passed back (unused)
 * @return     error code from D-Bus calls
 */
int sendSignal1(sd_bus_message *msg, void *userdata, sd_bus_error *retError)
{
    int sdbusErr = 0;
    char byteArray[] = {0xde, 0xad, 0xc0, 0xde};

    /* We have to reply even though its empty */
    sd_bus_reply_method_return(msg, "");


    /* Emit a signal. Usually this would go to another service (kind of silly to send a
     signal to yourself) but we are listening to ourselves in ObjB for ease of example */
    sdbusErr = sd_bus_emit_signal(pBus,
                                  objB_objectPath,
                                  objB_interfaceName,
                                  "Signal1",
                                  "y",
                                  byteArray);

    return sdbusErr;
}