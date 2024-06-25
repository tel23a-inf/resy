cmake_minimum_required(VERSION 3.10)

project("Reservierunssystem" LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
include_directories(test)
add_subdirectory(test)

include_directories(src)
add_subdirectory(src)

cmake_path(SET GITIGNORE_FILE NORMALIZE "${CMAKE_BINARY_DIR}/.gitignore")
file(WRITE ${GITIGNORE_FILE} "*")
