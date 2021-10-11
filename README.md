# DbusExamples
Example code in C using the linux sd-bus library

In needing to work with this library for a project I found the documentation sparse and the examples limited. My hope is that this repo can serve as a jumping off point for others in the future.

Please feel free to open a PR if you would like to contribute examples. I'd love for this to end up as comprehensive as the [freedesktop python examples](https://github.com/freedesktop/dbus-python/tree/master/examples)

## Prerequisites
`sudo apt install` the following:
- libsystemd-dev
- d-feet (optional for testing)

In order to allow dbus to register a service we need to add an entry to /etc/dbus-1/system.d/. `confFile.c` contains the necessary bus configurations, see the comments in that file for exact instructions

## How to build & run
```
mkdir build
cd build
camke ..
make
./dbusExample
```
### Clean
- Remove output binary: `make clean`
- Remove all generated files: `make clean-all`

## How do I know if it's working?
### List running services & call methods
- Open up `d-feet`
- Select "Session Bus"
- Look for a service called com.example.DbusServiceC
- If it's there then yay! Your dbus service is running
- You can check the service name, object path, interface name, and method name and arguments in d-feet

You can also use d-feet to call methods
- Find & click on your service in d-feet
- Navigate to your interface->method and double click
- A new window will pop up with a "Method Input" box allowing you to send data (click "Execute"), replies will appear in th "Method output" box
### Observe sent dbus messages
- Run `dbus-monitor` in the background or a separate terminal
- Send a dbus message
- dbus-monitor will show the traffic on the bus including message type (signal, method, method reply), time stamp, sender, destination, and contents

  Example:
  ```
  signal time=1633748547.920393 sender=org.freedesktop.DBus -> destination=(null destination) serial=880 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=NameOwnerChanged
    string ":1.414"
    string ":1.414"
    string ""
  
  method call time=1633748556.627750 sender=:1.415 -> destination=org.freedesktop.DBus serial=1 path=/org/freedesktop/DBus; interface=org.freedesktop.DBus; member=Hello
  
  method return time=1633748556.627837 sender=org.freedesktop.DBus -> destination=:1.415 serial=1 reply_serial=1
    string ":1.415"

  ```

