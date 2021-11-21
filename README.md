# sdbusExamples
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

# General dbus info

## Signals & Methods
A signal is a one part broadcast. A service sends out a message without receiving a reply.
> For example: The temp monitor will send out a signal when the temp changes. The main service can subscribe to this signal and trigger internal callbacks when a new signal is received.

A method consists of two parts, a received message and a sent reply. A method is called by another service.
> For example: The main service periodically sends update requests to the temp monitor (by calling the method) and the temp monitor replies with the updated temperature

## Servers & Clients
Each service can act as a server or a client with regards to another service. A server may have methods that clients can call and it may send out signals that clients can subscribe to. A single service can be both a server and a client at the same time.

> For example: The main service wants to receive messages about the temperature from the temp monitor and send messages to the fan controller. The temp monitor could act as a server and send out signals when the temperature changes, the main service would subscribe to that signal as a client. The main service could simultaneously act as a server and create a method which the fan controller (client) polls to give its status and receive new speed settings in the reply.
