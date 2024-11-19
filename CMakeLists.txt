cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#********************************************************
#                        Preamble                       *
#********************************************************
if(NOT UNIX)
    message(FATAL_ERROR "Non-UNIX systems not supported at this time.")
else()
    message(STATUS "Build system is a UNIX system. Continuing build.")
endif()

project(cnn-practice 
    VERSION 0.1.0
    LANGUAGES CXX
)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(WARNING "You are not using GCC.  Builds may succeed, but we cannot guarantee it.")
endif()

#********************************************************
#                 Global Build Options                  *
#********************************************************
add_compile_options(-std=c++2b -Wall -Wextra -Wpedantic -Werror)
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options(
        -O0   #May want to move this outside CMake.
        -g
        -fsanitize=address
        -fsanitize=leak
    )
endif()

#********************************************************
#                   Project Header                      *
#********************************************************
#Add subdirectories:
add_subdirectory(test)

set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
#target_sources(cnn-practice $CMAKE_CURRENT_LIST_DIR/src)



#*******************************************************
#                        Common:                       *
#*******************************************************
add_library(exceptions STATIC ${PROJECT_SOURCE_DIR}/exceptions.cpp)
target_include_directories(exceptions PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
#*******************************************************
#                        End Common                    *
#*******************************************************


#*******************************************************
#                        Tensor:                       *
#*******************************************************
add_library(tensor_internal STATIC ${PROJECT_SOURCE_DIR}/internal/tensor)
target_include_directories(tensor_internal PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(tensor_internal 
    exceptions
)

add_library(tensor STATIC ${PROJECT_SOURCE_DIR}/tensor.cpp)
target_include_directories(tensor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(tensor
    tensor_internal
    exceptions
)
#*******************************************************
#                        End Tensor                    *
#*******************************************************



if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
add_executable(cnn-practice
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/tensor.cpp
)

target_include_directories(cnn-practice
    PRIVATE $CMAKE_CURRENT_LIST_DIR/include
)
target_link_libraries(cnn-practice
    tensor
    exceptions
)
endif()
