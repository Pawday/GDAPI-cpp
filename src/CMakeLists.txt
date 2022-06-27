cmake_minimum_required(VERSION 3.10)
project(GDAPI)

cmake_policy(SET CMP0076 NEW)

set(CMAKE_CXX_STANDARD 11)

list(APPEND GD_API_SOURCES Level.cc)
list(APPEND GD_API_SOURCES LevelsManager.cc)
list(APPEND GD_API_SOURCES tools/MemoryBlock.cc)
list(APPEND GD_API_SOURCES tools/GDPlist.cc)

list(APPEND GD_API_SOURCES tools/crypt/GDXor.cc)
list(APPEND GD_API_SOURCES tools/crypt/GDCoder.cc)
list(APPEND GD_API_SOURCES tools/crypt/GDBase64.cc)
list(APPEND GD_API_SOURCES tools/crypt/GDPack.cc)

add_subdirectory(tools/crypt/z)

if (WIN32)
    list(APPEND GD_API_SOURCES platform/LevelsManagerFactory_win.cc)
endif (WIN32)

add_library(GDAPI-obj OBJECT)

target_link_libraries(GDAPI-obj PRIVATE z)

target_sources(GDAPI-obj PRIVATE ${GD_API_SOURCES})


target_include_directories(GDAPI-obj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(GDAPI-obj PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_library(GDAPI STATIC $<TARGET_OBJECTS:GDAPI-obj>)
target_link_libraries(GDAPI INTERFACE GDAPI-obj)
