cmake_minimum_required(VERSION 3.10)

project(GDAPI CXX)



add_subdirectory(src)


add_subdirectory(utils)


enable_testing()
add_subdirectory(tests)