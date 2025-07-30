cmake_minimum_required(VERSION 4.0)
project(Koby)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Koby
    src/main.cpp
    src/server.cpp
    src/request.cpp
    src/util.cpp
    src/response.cpp
    src/json.cpp
)

target_include_directories(Koby PRIVATE 
    include
    /usr/include/asio
)


target_link_libraries(Koby 
    pthread
)


