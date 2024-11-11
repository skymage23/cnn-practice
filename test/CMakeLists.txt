add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/third_party/googletest)

set(TESTS_SRC ${CMAKE_CURRENT_LIST_DIR}/src)
add_executable(tests
    ${TESTS_SRC}/tensor_tests.cpp
)
target_include_directories(tests PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/third_party/googletest/googletest/include
)

target_link_libraries(
    tests
    tensor
    GTest::gtest_main
)


include(GoogleTest)
gtest_add_tests(
    TARGET tests
    TEST_PREFIX "utest_"
)