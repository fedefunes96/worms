cmake_minimum_required(VERSION 2.8.12)
project (Worms)

set (PROJECT_LINK_LIBS Box2D.a)
link_directories( usr/local/lib )

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pthread -pedantic")

add_compile_options(-std=c++11 -pthread)

file(GLOB SOURCES "*.cpp")

add_executable(Worms ${SOURCES})
target_link_libraries(Worms ${PROJECT_LINK_LIBS})
