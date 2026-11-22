cmake_minimum_required(VERSION 3.24)

project(Examples3D
    DESCRIPTION "3D examples of the Crema rendering engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(BUILD_TESTS OFF CACHE BOOL "Disable Crema tests for examples" FORCE)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../.. ${CMAKE_CURRENT_BINARY_DIR}/crema)

add_executable(3d_hello_cube
    ${CMAKE_CURRENT_LIST_DIR}/3d_hello_cube.cpp
)

target_link_libraries(3d_hello_cube
    PRIVATE
        crema::crema
)

add_executable(3d_geometry_gallery
    ${CMAKE_CURRENT_LIST_DIR}/3d_geometry_gallery.cpp
)

target_link_libraries(3d_geometry_gallery
    PRIVATE
        crema::crema
)
