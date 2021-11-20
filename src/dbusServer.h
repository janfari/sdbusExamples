/******************************************************************************
* @file    dbusServer.h
* @brief
******************************************************************************/

#ifndef _DBUS_SERVER_
#define _DBUS_SERVER_

#include <systemd/sd-bus.h>

/* Method handlers*/
int method1Handler(sd_bus_message *msg, void *userdata, sd_bus_error *retError);
int sendSignal1(sd_bus_message *msg, void *userdata, sd_bus_error *retError);

/* Interface and path name strings */
static const char objA_objectPath[] = "/ObjectAPath";
static const char objA_interfaceName[] = "com.example.ObjectA";

/* This is the vtable for our object A. The vtable contains the specifications
 for the methods and signals within our object.
 The parameter type codes used are defined in the D-Bus specification
 https://dbus.freedesktop.org/doc/dbus-specification.html#type-system
 See also man pages for sd_bus_add_object_vtable and sd_bus_message_append */
static const sd_bus_vtable objA_vtable[] = {
    SD_BUS_VTABLE_START(0),
    /* Example method with strings and various int types */
    SD_BUS_METHOD_WITH_NAMES(
        "Method1_1",
        "si", SD_BUS_PARAM(msgString) SD_BUS_PARAM(msg32Int),
        "uxqs",
        SD_BUS_PARAM(reply32UInt)
        SD_BUS_PARAM(reply64UInt)
        SD_BUS_PARAM(reply16Int)
        SD_BUS_PARAM(replyString),
        method1Handler,
        SD_BUS_VTABLE_UNPRIVILEGED),
    /* Empty method which triggers Signal 1 for example purposes */
    SD_BUS_METHOD(
        "Method2",
        "",
        "",
        sendSignal1,
        SD_BUS_VTABLE_UNPRIVILEGED),
    /* Signal 1, triggered by sendSignal1(), sends a byte array */
    SD_BUS_SIGNAL_WITH_NAMES("Signal1",
                             "ay",
                             SD_BUS_PARAM(signalByteArray),
                             0),
    SD_BUS_VTABLE_END
};

#endif //_DBUS_SERVER_
