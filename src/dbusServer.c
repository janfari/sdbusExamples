/******************************************************************************
* @file    dbusClient.c
* @brief
******************************************************************************/

#include <stdlib.h>
#include "dbusServer.h"
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
    int receviedInt = 0;
    const char* receviedStr = NULL;

    /* Read the D-Bus message */
    sdbusErr = sd_bus_message_read(msg, "si", &receviedStr, &receviedInt);
    if (0 > sdbusErr)
    {
        printf("D-Bus Error: Failed to read message: %s\n", strerror(-sdbusErr));
    }
    else
    {
        printf("Method 1 on Object A was called, string: %s and int: %i were recevied\n",
        receviedStr, receviedInt);
    }

    /* Send various int types and a string as the reply */
    sd_bus_reply_method_return(msg, "uxqs", 1, 2, 3, "a string");

    return sdbusErr;
}
