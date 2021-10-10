/******************************************************************************
* @file    dbusServer.h
* @brief   
******************************************************************************/

#ifndef _DBUS_SERVER_
#define _DBUS_SERVER_

#include <systemd/sd-bus.h>

int method1Handler(sd_bus_message *msg, void *userdata, sd_bus_error *retError);

static const char objA_objectPath[] = "/ObjectAPath";
static const char objA_interfaceName[] = "com.example.ObjectA";

/* This is the vtable for our object A. The vtable contains the specifications 
 for the methods and signals within our object.
 The parameter type codes used are defined in the D-Bus specification 
 https://dbus.freedesktop.org/doc/dbus-specification.html#type-system
 See also man pages for sd_bus_add_object_vtable and sd_bus_message_append */
static const sd_bus_vtable objA_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_METHOD_WITH_NAMES(
        "Method1",
        "si", SD_BUS_PARAM(MsgString1) SD_BUS_PARAM(MsgInt1),
        "is", SD_BUS_PARAM(ReplyInt1) SD_BUS_PARAM(ReplyString1),
        method1Handler,
        SD_BUS_VTABLE_UNPRIVILEGED),
    SD_BUS_VTABLE_END
};

#endif //_DBUS_SERVER_