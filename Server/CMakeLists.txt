cmake_minimum_required(VERSION 2.8.12)
project (Server)

set (PROJECT_LINK_LIBS Box2D yaml-cpp)
link_directories( ${PATH}/lib )

include_directories("../Box2D")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/Stage")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Callbacks")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Environment")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables/Movables")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables/Movables/Missiles")
include_directories("${PROJECT_SOURCE_DIR}/Stage/Ubicables/Movables/Worms")
include_directories("${PROJECT_SOURCE_DIR}/Core")
include_directories("${PROJECT_SOURCE_DIR}/Communications")
include_directories("${PROJECT_SOURCE_DIR}/Communications/Events")
include_directories("${PROJECT_SOURCE_DIR}/Usables")
include_directories("../Common")
#include_directories( ../Escenario/GameWindow )

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pthread -pedantic")

add_compile_options(-std=c++11 -pthread)

file(GLOB SOURCES "*.cpp" 
"Stage/*.cpp"
"Stage/Callbacks/*.cpp"
"Stage/Environment/*.cpp"
"Stage/Ubicables/*.cpp"
"Stage/Ubicables/Movables/*.cpp"
"Stage/Ubicables/Movables/Missiles/*.cpp"
"Stage/Ubicables/Movables/Worms/*.cpp"
"Core/*.cpp"
"Communications/*.cpp"
"Communications/Events/*.cpp"
"Usables/*.cpp"
"../Common/*.cpp")
#"../Escenario/GameWindow/socket.cpp"
#"../Escenario/GameWindow/protocol.cpp")

add_executable(Server ${SOURCES} )
target_link_libraries(Server ${PROJECT_LINK_LIBS})
install(TARGETS Server DESTINATION bin)
