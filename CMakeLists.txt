cmake_minimum_required(VERSION 3.17)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)
include_directories(gl_libs utils render)
add_executable(ray_tracing main.cpp gl_libs/glad.c gl_libs/stb_image.c render/ray.h utils/Png_Image.h utils/utility.h utils/Png_Image.h render/hittable.h render/sphere.h render/hittable_list.h render/camera.h)
target_link_libraries(ray_tracing glfw3 pthread GL Xrandr Xi X11 Xxf86vm dl Xinerama Xcursor assimp)