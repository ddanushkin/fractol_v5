cmake_minimum_required(VERSION 3.14)
project(fractol_v5 C)

set(CMAKE_C_STANDARD 99)

add_executable(fractol_v5 src/main.c includes/fractol.h)

target_link_libraries(fractol_v5 "-lmlx")
target_link_libraries(fractol_v5 "-framework OpenGl")
target_link_libraries(fractol_v5 "-framework Appkit")
target_link_libraries(fractol_v5 "-pthread")