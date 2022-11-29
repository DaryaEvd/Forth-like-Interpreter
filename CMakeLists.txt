cmake_minimum_required(VERSION 3.20)
project(ForthLikeInterpreter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(src
        src/main.cpp
        src/commands.cpp
        )
 

SET(WARN_FLAGS "-Wall -Wpedantic -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARN_FLAGS} ${ASAN_OPTIONS}") 
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
 
