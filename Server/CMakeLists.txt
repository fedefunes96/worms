cmake_minimum_required(VERSION 2.8.12)
project (Worms)

set (PROJECT_LINK_LIBS Box2D.a yaml-cpp)
#link_directories( usr/local/lib )

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Events")
include_directories("${PROJECT_SOURCE_DIR}/Stage")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Callbacks")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Environment")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables/Movables")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables/Movables/Missiles")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables/Movables/Worms")
include_directories("${PROJECT_SOURCE_DIR}/Server")
include_directories("${PROJECT_SOURCE_DIR}/Communications")
include_directories("${PROJECT_SOURCE_DIR}/Usables")
include_directories("../Common")
#include_directories( ../Escenario/GameWindow )

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pthread -pedantic -lyaml-cpp")

add_compile_options(-std=c++11 -pthread)

file(GLOB SOURCES "*.cpp" 
"Events/*.cpp"
"Stage/*.cpp"
"Stage/Callbacks/*.cpp"
"Stage/Environment/*.cpp"
"Stage/Ubicables/*.cpp"
"Stage/Ubicables/Movables/*.cpp"
"Stage/Ubicables/Movables/Missiles/*.cpp"
"Stage/Ubicables/Movables/Worms/*.cpp"
"Server/*.cpp"
"Communications/*.cpp"
"Usables/*.cpp"
"../Common/*.cpp")
#"../Escenario/GameWindow/socket.cpp"
#"../Escenario/GameWindow/protocol.cpp")

add_executable(Worms ${SOURCES} )
target_link_libraries(Worms ${PROJECT_LINK_LIBS})
install(TARGETS Worms DESTINATION bin)
