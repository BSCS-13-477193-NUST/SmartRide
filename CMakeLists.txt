cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SmartRide)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(csv-parser)

#includes
include_directories(include)

#add the sources
file(GLOB_RECURSE SOURCES "src/*/*.cpp")
file(GLOB_RECURSE SOURCES "src/*.cpp")


# Add the executable
add_executable(SmartRide main.cpp ${SOURCES})
target_link_libraries(SmartRide csv)