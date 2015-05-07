cmake_minimum_required(VERSION 3.0)
project(trackmc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_FILES
    trackmc/Exceptions.cpp
    trackmc/Gas.cpp
    trackmc/GasMixture.cpp
    trackmc/Particle.cpp
    trackmc/Vector3D.cpp
    trackmc/TrackSimulator.cpp
    trackmc/InputFile.cpp
    trackmc/EventGenerator.cpp
    trackmc/PadPlane.cpp)

set(TEST_FILES
    tests/Particle_tests.cpp
    tests/Vector3D_tests.cpp
    tests/Gas_tests.cpp
    tests/GasMixture_tests.cpp
    tests/TrackSimulator_tests.cpp
    tests/InputFile_tests.cpp
    tests/EventGenerator_tests.cpp)

set(MAIN_FILE trackmc/main.cpp)
set(TEST_MAIN_FILE tests/catch_main.cpp)

include_directories(trackmc)

find_library(LIBYAMLCPP NAMES libyaml-cpp.a PATHS /usr/local/lib)

add_subdirectory(get-manip)

add_executable(trackmc ${SOURCE_FILES} ${MAIN_FILE})
add_executable(trackmc_tests ${SOURCE_FILES} ${TEST_FILES} ${TEST_MAIN_FILE})

target_link_libraries(trackmc ${LIBYAMLCPP} getevt)
target_link_libraries(trackmc_tests ${LIBYAMLCPP} getevt)
