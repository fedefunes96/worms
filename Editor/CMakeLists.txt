cmake_minimum_required(VERSION 3.1.0)

project(Editor)
set (PROJECT_LINK_LIBS yaml-cpp)

link_directories(usr/local/lib)

include_directories("${PROJECT_SOURCE_DIR}/Conteiner")
include_directories("${PROJECT_SOURCE_DIR}/Save-Load")
include_directories("${PROJECT_SOURCE_DIR}/Windows")
include_directories("${PROJECT_SOURCE_DIR}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

SET(CMAKE_CXX_FLAGS " -std=c++0x -lyaml-cpp")

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

find_package(yaml-cpp REQUIRED)


# Populate a CMake variable with the sources
file(GLOB SOURCE *.cpp *.ui
"*.cpp"
"Conteiner/*.cpp"
"Save-Load/*.cpp"
"Windows/*.cpp") 
# Tell CMake to create the helloworld executable
add_executable(Editor ${SOURCE})
# Use the Widgets module from Qt 5
target_link_libraries(Editor Qt5::Widgets)
target_link_libraries(Editor ${YAML_CPP_LIBS} ${PROJECT_LINK_LIBS})
install(TARGETS Editor DESTINATION bin)
