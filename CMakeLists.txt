cmake_minimum_required(VERSION 3.12)
project(cpp_cheatsheet)

# TODO: compile submodules with different std version
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CompileFiles)

add_subdirectory(basic)
add_subdirectory(stl)
add_subdirectory(std)
add_subdirectory(idioms)
add_subdirectory(temp)
add_subdirectory(libtest)
add_subdirectory(app)
