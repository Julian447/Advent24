cmake_minimum_required(VERSION 3.30)
project(d7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_subdirectory(source)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE handle_file)
