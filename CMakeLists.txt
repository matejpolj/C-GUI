cmake_minimum_required(VERSION 3.25)
project(C_GUI C)

set(CMAKE_C_STANDARD 11)

add_executable(C_GUI main.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

target_link_libraries(C_GUI ${GTK_LIBRARIES})