/******************************************************************************
* @file    dbusClient.h
* @brief
******************************************************************************/

#ifndef _DBUS_CLIENT_
#define _DBUS_CLIENT_

#include <systemd/sd-bus.h>

/* Callback Handlers */
int signalCallback(sd_bus_message *pMsg, void *pUserdata, sd_bus_error *pRetError);

/* Interface and path name strings  */
static const char objB_objectPath[] = "/ObjectBPath";
static const char objB_interfaceName[] = "com.example.ObjectB";

/* This is the vtable for our object A. The vtable contains the specifications
 for the methods and signals within our object.
 The parameter type codes used are defined in the D-Bus specification
 https://dbus.freedesktop.org/doc/dbus-specification.html#type-system
 See also man pages for sd_bus_add_object_vtable and sd_bus_message_append */
static const sd_bus_vtable objB_vtable[] = {
    SD_BUS_VTABLE_START(0),
    SD_BUS_VTABLE_END
};


#endif //_DBUS_CLIENT_
