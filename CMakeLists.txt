cmake_minimum_required(VERSION 3.17)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
endif()

include_directories(gl_libs utils render)
add_executable(ray_tracing main.cpp gl_libs/glad.c gl_libs/stb_image.c render/ray.h utils/Png_Image.h utils/utility.h utils/Png_Image.h physics/hittable.h physics/sphere.h physics/hittable_list.h utils/camera.h texture/material.h)
target_link_libraries(ray_tracing glfw3 pthread GL Xrandr Xi X11 Xxf86vm dl Xinerama Xcursor assimp)