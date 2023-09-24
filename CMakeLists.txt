cmake_minimum_required(VERSION 3.15)

project(LogiXpr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Google C++ Testing Framework
cmake_policy(SET CMP0135 NEW)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

include_directories(${INCLUDE_DIR})

file(GLOB SOURCE_FILES ${SOURCE_DIR}/*.cpp)
file(GLOB TESTS_FILES ${TESTS_DIR}/*.cpp)

add_executable(LogiXpr ${SOURCE_FILES} main.cpp)

# Testing 
enable_testing()

add_executable(tests ${TESTS_FILES} ${SOURCE_FILES} ${INCLUDE_DIR})

target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

# copy config file to build directory
# check if debug or release folder exists
message("Copying config file...")
if(NOT EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
  file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
  configure_file(config.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/config.ini COPYONLY)
else()
  configure_file(config.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/config.ini COPYONLY)
endif()

if(NOT EXISTS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
  file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release)
  configure_file(config.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/config.ini COPYONLY)
else()
  configure_file(config.ini ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/config.ini COPYONLY)
endif()