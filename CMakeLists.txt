cmake_minimum_required(VERSION 3.2)
project(trackmc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    trackmc/Exceptions.cpp
    trackmc/Gas.cpp
    trackmc/Particle.cpp
    trackmc/Vector3D.cpp)

set(TEST_FILES
    tests/Particle_tests.cpp)

set(MAIN_FILE trackmc/main.cpp)
set(TEST_MAIN_FILE tests/catch_main.cpp)

include_directories(trackmc)

add_executable(trackmc ${SOURCE_FILES} ${MAIN_FILE})
add_executable(trackmc_tests ${SOURCE_FILES} ${TEST_FILES} ${TEST_MAIN_FILE})