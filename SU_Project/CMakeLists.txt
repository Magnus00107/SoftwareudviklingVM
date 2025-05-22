cmake_minimum_required(VERSION 3.10)
project(SU_Game)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(header)

# Find all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(su_game ${SOURCES})
