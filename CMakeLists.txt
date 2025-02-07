cmake_minimum_required(VERSION 3.10)

# Set the project name
project(pong)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(3rdParty/SDL EXCLUDE_FROM_ALL)

# Add an executable target
add_executable(pong src/main.cpp)

target_link_libraries(pong PRIVATE SDL3::SDL3)
