cmake_minimum_required(VERSION 3.2)
project(CellularAutomata LANGUAGES CXX C)

message("This script is running") # Prints to the console

add_executable(main src/main.cpp src/application.cpp src/Grid.cpp) # Source files to be compiled

target_include_directories(main PUBLIC include) # Header files to be included and compiled

# Searches the System for the OpenGL library
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    message("OpenGL library file is present at ${OPENGL_LIBRARY}")
endif(OPENGL_FOUND)

set(sfml_libs ${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML)
target_link_libraries(main ${sfml_libs}/libsfml-graphics-s.a ${sfml_libs}/libsfml-window-s.a ${sfml_libs}/libsfml-system-s.a ${OPENGL_LIBRARY} winmm.lib)