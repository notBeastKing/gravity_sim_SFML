cmake_minimum_required(VERSION 3.24) #we have to tell what version of cmake we are using
project(SFML_1) #here we give the project name

add_executable(game1 main.cpp)
#adding an executable and the file it has to compile into the executable
#add_executable(exename cppfile ....(more headers/files to compile))

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR  C:/SFML-64/lib/cmake/SFML)
find_package(SFML COMPONENTS audio graphics network system window)

include_directories(C:/SFML-64/include)

target_link_libraries(game1 sfml-audio sfml-graphics sfml-main sfml-network sfml-system sfml-window)
