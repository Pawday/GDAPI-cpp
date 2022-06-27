cmake_minimum_required(VERSION 3.10)

project(GDAPI_Z)

add_library(z-obj OBJECT)

list(APPEND Z_SOURCES inflate.c)
list(APPEND Z_SOURCES crc32.c)
list(APPEND Z_SOURCES adler32.c)
list(APPEND Z_SOURCES inffast.c)
list(APPEND Z_SOURCES inftrees.c)
list(APPEND Z_SOURCES zutil.c)

target_sources(z-obj PRIVATE ${Z_SOURCES})

target_include_directories(z-obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inclpub)

add_library(z STATIC $<TARGET_OBJECTS:z-obj>)
target_link_libraries(z INTERFACE z-obj)