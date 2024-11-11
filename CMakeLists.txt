cmake_minimum_required(VERSION 3.10)
project(cnn-practice 
    VERSION 0.1.0
    LANGUAGES CXX
)

#Add subdirectories:
add_subdirectory(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
#target_sources(cnn-practice $CMAKE_CURRENT_LIST_DIR/src)
add_executable(cnn-practice
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/matrix.cpp
)
target_include_directories(cnn-practice
    PRIVATE $CMAKE_CURRENT_LIST_DIR/include
)


add_library(exceptions STATIC ${PROJECT_SOURCE_DIR}/exceptions.cpp)
target_include_directories(exceptions PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(matrix STATIC ${PROJECT_SOURCE_DIR}/matrix.cpp)
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(matrix
    exceptions
)


target_link_libraries(cnn-practice
    matrix
    exceptions
)
