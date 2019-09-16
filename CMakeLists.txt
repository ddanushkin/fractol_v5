cmake_minimum_required(VERSION 3.14)
project(fractol_v5 C)

set(CMAKE_C_STANDARD 99)
file(GLOB_RECURSE PROJ_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "libft/sources/*.c")
add_executable(fractol_v5 src/main.c includes/fractol.h libft/includes/libft.h)
#		libft/ft_putstr.c
#		libft/ft_strcmp.c
#		libft/ft_putchar.c)

target_link_libraries(fractol_v5 "-pthread")
target_link_libraries(fractol_v5 "-lmlx")
target_link_libraries(fractol_v5 "-framework OpenGl")
target_link_libraries(fractol_v5 "-framework Appkit")
