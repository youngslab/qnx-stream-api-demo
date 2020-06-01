
cmake_minimum_required(VERSION 3.10)

project(qnx-stream)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

find_package(screen REQUIRED)

add_executable(producer producer/error.c producer/gears.c producer/gles2-gears.c)
target_link_libraries(producer screen::screen EGL GLESv2 m)
set_target_properties(producer PROPERTIES CXX_STANDARD 17)

add_executable(consumer consumer/main.cpp)
target_link_libraries(consumer screen::screen EGL GLESv2)
set_target_properties(consumer PROPERTIES CXX_STANDARD 17)

