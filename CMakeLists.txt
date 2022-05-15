cmake_minimum_required(VERSION 3.15)
project(nuclear_fusion)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

link_directories(${PROJECT_SOURCE_DIR})

add_library(nf_lib SHARED src/nf.cpp)
add_library(window_lib SHARED src/window.cpp)
add_library(brush_lib SHARED src/brush.cpp)


add_executable(main main.cpp src/window.cpp src/brush.cpp)
target_link_libraries(main window_lib brush_lib nf_lib sfml-graphics)

find_package(pybind11 REQUIRED)
pybind11_add_module(nuclear_fusion bindings.cpp)
target_link_libraries(nuclear_fusion PUBLIC window_lib brush_lib nf_lib sfml-graphics)
