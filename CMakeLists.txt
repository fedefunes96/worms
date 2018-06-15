cmake_minimum_required(VERSION 2.8.12)
project (Worms)

add_subdirectory(Server)
add_subdirectory(Editor)
add_subdirectory(Escenario/GameWindow)

file(COPY "yaml" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "images" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
