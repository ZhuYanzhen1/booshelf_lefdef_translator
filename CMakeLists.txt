cmake_minimum_required(VERSION 3.24)
project(translator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_INSTALL_RPATH "lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

add_custom_target(update_version_file ALL
        COMMAND ${CMAKE_COMMAND} -E echo "Updating version.h"
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/version.cmake
        DEPENDS ${CMAKE_SOURCE_DIR}/version.cmake
)

add_compile_options(-Og -g)
include_directories(parser database tclap)

file(GLOB_RECURSE SOURCES "parser/*.cc" "database/*.cc" "exporter/*.cc")

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(${PROJECT_NAME} ${SOURCES} main.cc)
target_link_libraries(${PROJECT_NAME} stdc++fs pthread -static)
add_dependencies(${PROJECT_NAME} update_version_file)
