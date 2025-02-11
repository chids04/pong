cmake_minimum_required(VERSION 3.10)

project(pong)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(boost_asio CONFIG REQUIRED)

add_subdirectory(deps/SDL EXCLUDE_FROM_ALL)
add_subdirectory(deps/SDL_ttf EXCLUDE_FROM_ALL)
#add_subdirectory(server)

add_executable(pong 
    src/main.cpp
    src/gamemanager.cpp
    src/ball.cpp)

target_include_directories(pong PRIVATE src/ )   

target_link_libraries(pong PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3 Boost::asio)
