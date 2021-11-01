cmake_minimum_required(VERSION 3.1)
project(dbusExamples C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

include_directories("${CMAKE_SOURCE_DIR}/src")

set(SOURCE_FILES src/main.c)
add_executable(dbusExample ${SOURCE_FILES}
src/dbus.h
src/dbusClient.h
src/dbusClient.c
src/dbusServer.h
src/dbusServer.c)

install(TARGETS dbusExample
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/)

add_custom_target(clean-all
  make clean && rm -fR ${CMAKE_BINARY_DIR}/CMakeCache.txt
                       ${CMAKE_BINARY_DIR}/cmake_install.cmake
                       ${CMAKE_BINARY_DIR}/Makefile
                       ${CMAKE_BINARY_DIR}/CMakeFiles
)

find_library(SYSTEMD systemd)
target_link_libraries(dbusExample ${SYSTEMD})
