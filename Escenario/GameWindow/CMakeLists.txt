cmake_minimum_required(VERSION 3.1.0)

project(GameWindow)

link_directories(usr/local/lib)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

SET(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++0x")

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)


# Populate a CMake variable with the sources
file(GLOB SOURCE *.cpp *.ui) 
# Tell CMake to create the helloworld executable
add_executable(GameWindow ${SOURCE})
# Use the Widgets module from Qt 5
target_link_libraries(GameWindow Qt5::Widgets Qt5::Multimedia)
install(TARGETS GameWindow DESTINATION bin)
