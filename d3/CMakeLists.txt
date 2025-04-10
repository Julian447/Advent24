cmake_minimum_required(VERSION 3.30)
project(d1)

set(CMAKE_CXX_STANDARD 20)


include_directories(include)
add_subdirectory(handle_file)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE handle_file)
