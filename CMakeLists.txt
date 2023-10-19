cmake_minimum_required(VERSION 3.0.0)

project(c_project_generator)

## set c compiler
set(CMAKE_C_COMPILER "gcc")

## set c version
set(CMAKE_C_STANDARD 17)


## set c flags
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpedantic -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-but-set-parameter -Wno-unused-value -Wno-unused-result -Wno-unused-label -Wno-unused-local-typedefs -Wno-unused-macros -Wno-unused-const-variable -Wno-unused-const-variable -Wno-unused-const-parameter -Wno-unused-const-variable -Wno-unused-cons ")


                    
file (GLOB SOURCES "src/*.c")
                    
add_executable(${PROJECT_NAME} ${SOURCES})

message(STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS})
message(STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER})
message(STATUS "CMAKE_C_STANDARD: " ${CMAKE_C_STANDARD})
message(STATUS "Final Project Name: " ${PROJECT_NAME})


install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)

