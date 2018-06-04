cmake_minimum_required(VERSION 3.1.0)

project(Sound)

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
find_package(Qt5Multimedia REQUIRED)

# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Populate a CMake variable with the sources
file(GLOB SOURCE *.cpp *.ui) 
# Tell CMake to create the helloworld executable
add_executable(Sound ${SOURCE})
# Use the Widgets module from Qt 5
target_link_libraries(Sound Qt5::Widgets Qt5::Multimedia)
target_link_libraries(Sound ${PROJECT_LINK_LIBS})
