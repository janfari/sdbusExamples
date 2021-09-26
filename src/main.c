#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <systemd/sd-bus.h>
#include "dbusClient.h"

/* This name is permitted in /etc/dbus-1/system.d/com.example.DbusServiceC.conf
 * To change this service name, the .conf will need to be edited accordingly */
const char dbusServiceName[] = "com.example.DbusServiceC";
sd_bus * bus = NULL;


/**
 * @brief      Main loop to start and maintain the dbus framework
 * @return     sdbusErr sd_bus error code
 **/
int main()
{
    int sdbusErr = 0;

    /* Connect to the user (session) bus. */
    sdbusErr = sd_bus_default_user(&bus);
    /* This would connect you to the system bus instead
    sdbusErr = sd_bus_default_system(&bus); */

    /* sd_bus calls return negative values to indicate errors */
    if (sdbusErr < 0)
    {
        printf("D-Bus: Failed to connect to user bus:%s\n", strerror(-sdbusErr));
        
        /* Clean up by releasing the bus */
        sd_bus_unref(bus);
        return sdbusErr;
    }

    /* Take a pre-defined unique service name */
    sdbusErr = sd_bus_request_name(bus, dbusServiceName, 0);

    if (0 > sdbusErr)
    {
        printf("D-Bus: Failed to request service name: %s\n", strerror(-sdbusErr));
        sd_bus_unref(bus);
        return sdbusErr;
    }

    for (;;)
    {
        /* Process D-Bus requests */
        sdbusErr = sd_bus_process(bus, NULL);

        if (0 > sdbusErr)
        {
            printf("D-Bus: Failed to process bus: %s\n", strerror(-sdbusErr));
            /* We failed so try again with no delay */
            continue;
        }

        /* Wait (in usecs) for the next request to be ready */
        sdbusErr = sd_bus_wait(bus, 100);

        if (0 > sdbusErr)
        {
            printf("D-Bus: Failed to wait for bus: %s\n", strerror(-sdbusErr));
        }

    }

    /* Clean up */
    sd_bus_unref(bus);
    return sdbusErr;
}
