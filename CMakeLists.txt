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

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	link_directories(/usr/local/lib)
	target_link_libraries(PixelEdit glfw3 GL 
	# glfw3 library dependencies
	glfw3 rt Xrandr Xinerama Xi Xcursor m dl Xrender drm Xdamage X11-xcb 
		xcb-glx xcb-dri2 xcb-dri3 xcb-present xcb-sync xshmfence Xxf86vm 
		Xfixes Xext X11 pthread xcb Xau Xdmcp
	)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_link_libraries(PixelEdit opengl32 ${PROJECT_ROOT_DIR}/lib/glfw3)
endif()

set (CMAKE_CXX_FLAGS "-std=c++11")



include_directories(${PROJECT_ROOT_DIR}/include)
