cmake_minimum_required(VERSION 3.17)
project(sys_monitor LANGUAGES C VERSION 1.0.0 DESCRIPTION "System monitoring library")

set(CMAKE_C_STANDARD 99)

add_library(
    sys_monitor SHARED
        sys_monitor_api.c sys_monitor_api.h sys_monitor_internals.c sys_monitor_internals.h)