cmake_minimum_required(VERSION 3.1.0) 
project(Client)

link_directories(usr/local/lib)

include_directories("${PROJECT_SOURCE_DIR}/Stage")
include_directories("${PROJECT_SOURCE_DIR}/Communication")
include_directories("${PROJECT_SOURCE_DIR}/Game")
include_directories("${PROJECT_SOURCE_DIR}/Game/Event")
include_directories("${PROJECT_SOURCE_DIR}/Game/Item")
include_directories("${PROJECT_SOURCE_DIR}/Game/Item/Girder")
include_directories("${PROJECT_SOURCE_DIR}/Game/Item/Movable")
include_directories("${PROJECT_SOURCE_DIR}/Game/Item/Movable/Projectile")
include_directories("${PROJECT_SOURCE_DIR}/Game/Item/Movable/Worm")
include_directories("${PROJECT_SOURCE_DIR}/Game/Player")
include_directories("${PROJECT_SOURCE_DIR}/Game/Weapon")
include_directories("${PROJECT_SOURCE_DIR}/Controller")
include_directories("${PROJECT_SOURCE_DIR}/Sound")
include_directories("${PROJECT_SOURCE_DIR}/View")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("../Common")


file(GLOB SOURCES *.cpp *.ui
"*.cpp" 
"Communication/*.cpp"
"Stage/*.cpp"
"Game/*.cpp"
"Game/Event/*.cpp"
"Game/Item/*.cpp"
"Game/Item/Girder/*.cpp"
"Game/Item/Movable/*.cpp"
"Game/Item/Movable/Projectile/*.cpp"
"Game/Item/Movable/Worm/*.cpp"
"Game/Player/*.cpp"
"Game/Weapon/*.cpp"
"Controller/*.cpp"
"Sound/*.cpp"
"View/*.cpp"
"../Common/*.cpp")


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 -pthread -pedantic")

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)


# Populate a CMake variable with the sources
#file(GLOB SOURCE *.cpp *.ui) 
# Tell CMake to create the helloworld executable
add_executable(Client ${SOURCES})
# Use the Widgets module from Qt 5
target_link_libraries(Client Qt5::Widgets Qt5::Multimedia)
install(TARGETS Client DESTINATION bin)
