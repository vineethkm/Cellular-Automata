cmake_minimum_required(VERSION 3.20)
project(CellularAutomata LANGUAGES CXX)

add_subdirectory(SFML)

add_executable(main src/main.cpp src/Application.cpp src/Grid.cpp) # Source files to be compiled

if(WIN32)
  # Add windows specific cmake commands
endif()

target_include_directories(main PUBLIC include SFML/include) # Header files to be included and compiled

target_link_libraries(main sfml-graphics)
