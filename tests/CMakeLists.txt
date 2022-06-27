project(GDAPI_TESTS CXX)

list(APPEND GDAPI_TESTS CreateLevelsManager)
list(APPEND GDAPI_TESTS PListCreate)

enable_testing()

foreach(TEST_NAME ${GDAPI_TESTS})
    add_executable(${TEST_NAME}_test ${TEST_NAME}.cc)
    target_link_libraries(${TEST_NAME}_test PRIVATE GDAPI)
    add_test(${TEST_NAME} ${TEST_NAME}_test)
endforeach()


