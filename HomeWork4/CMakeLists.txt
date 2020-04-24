cmake_minimum_required(VERSION 3.15)
project(teach_project)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES main.cpp)


add_executable(teach_project ${SOURCES})

add_subdirectory(strategies)
add_subdirectory(game)

target_link_libraries(teach_project strategies game)
