cmake_minimum_required(VERSION 2.6)
project (PixelEdit)

set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)
set(PIXEL_EDIT_SRCS
    ${PROJECT_SOURCE_DIR}/input.cpp
    ${PROJECT_SOURCE_DIR}/renderer.cpp
    ${PROJECT_SOURCE_DIR}/state.cpp
    ${PROJECT_SOURCE_DIR}/main.cpp)
add_executable(PixelEdit ${PIXEL_EDIT_SRCS})

target_link_libraries(PixelEdit opengl32 ${PROJECT_ROOT_DIR}/lib/glfw3)

include_directories(${PROJECT_ROOT_DIR}/include)
