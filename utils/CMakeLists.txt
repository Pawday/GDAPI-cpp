project(GDAPI_UTILS)



add_executable(unpack_local unpack_local.cc)
target_link_libraries(unpack_local GDAPI)
