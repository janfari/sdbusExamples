# DbusExamples
Example code using the linux sd-bus library

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

### How do I know if it's working?
- Open up `d-feet`
- Select "Session Bus"
- Look for a service called com.example.DbusServiceC
- If its there then yay! Your dbus serrvice is running