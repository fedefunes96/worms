cmake_minimum_required(VERSION 2.8.12)
project (Worms)

set (PROJECT_LINK_LIBS Box2D.a)
link_directories( usr/local/lib )

include_directories( ../Escenario/Game_worms )
#include_directories( BEFORE ${MY_SOURCE_DIR}/src )

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pthread -pedantic")

add_compile_options(-std=c++11 -pthread)

file(GLOB SOURCES "*.cpp" 
"../Escenario/Game_worms/common_socket.cpp"
"../Escenario/Game_worms/protocol.cpp")

add_executable(Worms ${SOURCES} )
target_link_libraries(Worms ${PROJECT_LINK_LIBS})
