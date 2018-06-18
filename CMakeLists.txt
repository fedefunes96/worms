cmake_minimum_required(VERSION 2.8.12)

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
	set(PATH ${CMAKE_CURRENT_BINARY_DIR})
	add_definitions(-DROOT_PATH="${CMAKE_CURRENT_BINARY_DIR}")
else()
	set(PATH ${CMAKE_INSTALL_PREFIX})
	add_definitions(-DROOT_PATH="${CMAKE_INSTALL_PREFIX}")
endif()

project (Worms)

add_subdirectory(Server)
add_subdirectory(Editor)
add_subdirectory(Escenario/GameWindow)

file(COPY "yaml" DESTINATION ${PATH})
file(COPY "images" DESTINATION ${PATH})
file(COPY "resources" DESTINATION ${PATH})
file(COPY "sounds" DESTINATION ${PATH})
