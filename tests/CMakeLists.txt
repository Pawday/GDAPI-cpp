add_executable(MainTest CreateLevelsManager.cpp)

project(GDAPI_TESTS CXX)


add_executable(CreateLevelsManager CreateLevelsManager.cpp)

target_link_libraries(CreateLevelsManager PRIVATE GDAPI)

enable_testing()
add_test(CreateLevelsManagerTest CreateLevelsManager)
