cmake_minimum_required(VERSION 3.10)
project(cnn-practice 
    VERSION 0.1.0
    LANGUAGES CXX
)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
#target_sources(cnn-practice $CMAKE_CURRENT_LIST_DIR/src)
add_executable(cnn-practice
    ${PROJECT_SOURCE_DIR}/main.cpp
)
target_include_directories(cnn-practice
    PRIVATE $CMAKE_CURRENT_LIST_DIR/include
)