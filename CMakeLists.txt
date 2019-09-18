cmake_minimum_required(VERSION 3.14)

file(GLOB_RECURSE PROJ_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
file(GLOB_RECURSE LIBFT_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libft/*.c")

project(fractol_v5 C)
set(CMAKE_C_STANDARD 99)

include_directories("includes")
include_directories("libft/includes")

add_executable(fractol_v5 ${PROJ_SOURCES} ${LIBFT_SOURCES})

target_link_libraries(fractol_v5 "-pthread")
target_link_libraries(fractol_v5 "-lmlx")
target_link_libraries(fractol_v5 "-framework OpenGl")
target_link_libraries(fractol_v5 "-framework Appkit")

