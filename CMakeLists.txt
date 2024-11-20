cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SmartRide)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#includes
include_directories(include)

#add the sources
set(SOURCES src/*.cpp src/*/*.cpp)


# Add the executable
add_executable(SmartRide main.cpp SOURCES)