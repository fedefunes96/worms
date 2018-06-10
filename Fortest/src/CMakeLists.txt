cmake_minimum_required(VERSION 2.8.12)
project (Worms)

set (PROJECT_LINK_LIBS Box2D.a yaml-cpp)
link_directories( usr/local/lib )

include_directories( ../Escenario/GameWindow )

#include_directories( BEFORE ${MY_SOURCE_DIR}/src )

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pthread -pedantic -lyaml-cpp")

add_compile_options(-std=c++11 -pthread)

file(GLOB SOURCES "*.cpp" 
"../Escenario/GameWindow/socket.cpp"
"../Escenario/GameWindow/protocol.cpp")

add_executable(Worms ${SOURCES} )
target_link_libraries(Worms ${PROJECT_LINK_LIBS})
