cmake_minimum_required(VERSION 3.10)

project(pong-server)

find_package(boost_asio CONFIG REQUIRED)

add_executable(pong-server 
    src/server.cpp)

target_link_libraries(pong-server PRIVATE Boost::asio)
