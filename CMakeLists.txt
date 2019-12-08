cmake_minimum_required(VERSION 3.6.2)
#set(CMAKE_C_COMPILER /cygdrive/s/program_files/cygwin/bin/gcc.exe CACHE PATH "" FORCE)
#set(CMAKE_CXX_COMPILER /cygdrive/s/program_files/cygwin/bin/g++.exe CACHE PATH "" FORCE)
project(fractol C)
set(CMAKE_C_STANDARD 90)
include_directories(.)
include_directories(libft)
include_directories(headers)

#--------------LIB LINK EXAMPLE---------------------
#add_executable(<exe_name> sorce1 source2)
#find_library(FT ft libft)
#target_link_libraries(<exe_name> LINK_PUBLIC ${FT})
#---------------------------------------------------

add_executable(fractol
		src/main.c
		src/app.c
		src/controller.c
		src/camera.c
		src/framebuffer.c
		src/threads_test.c
		src/palette.c
		src/fractol.c
		src/fractol_pix.c
		src/it_estimator.c
		src/fractol_v2.c
		src/mouse_movement.c

		libft/src/string/ft_atoi.c
		libft/src/string/ft_bzero.c
		libft/src/string/ft_isalnum.c
		libft/src/string/ft_isalpha.c
		libft/src/string/ft_isascii.c
		libft/src/string/ft_isdigit.c
		libft/src/string/ft_isprint.c
		libft/src/string/ft_memalloc.c
		libft/src/string/ft_memccpy.c
		libft/src/string/ft_memchr.c
		libft/src/string/ft_memcmp.c
		libft/src/string/ft_memcpy.c
		libft/src/string/ft_memdel.c
		libft/src/string/ft_memmove.c
		libft/src/string/ft_memset.c
		libft/src/string/ft_putchar.c
		libft/src/string/ft_putchar_fd.c
		libft/src/string/ft_putendl.c
		libft/src/string/ft_putendl_fd.c
		libft/src/string/ft_putnbr.c
		libft/src/string/ft_putnbr_fd.c
		libft/src/string/ft_putstr.c
		libft/src/string/ft_putstr_fd.c
		libft/src/string/ft_strcat.c
		libft/src/string/ft_strchr.c
		libft/src/string/ft_strclr.c
		libft/src/string/ft_strcmp.c
		libft/src/string/ft_strcpy.c
		libft/src/string/ft_strdel.c
		libft/src/string/ft_strdup.c
		libft/src/string/ft_strequ.c
		libft/src/string/ft_striter.c
		libft/src/string/ft_striteri.c
		libft/src/string/ft_strjoin.c
		libft/src/string/ft_strlcat.c
		libft/src/string/ft_strlcpy.c
		libft/src/string/ft_strlen.c
		libft/src/string/ft_strmap.c
		libft/src/string/ft_strmapi.c
		libft/src/string/ft_strncat.c
		libft/src/string/ft_strncmp.c
		libft/src/string/ft_strncpy.c
		libft/src/string/ft_strnequ.c
		libft/src/string/ft_strnew.c
		libft/src/string/ft_strnstr.c
		libft/src/string/ft_strrchr.c
		libft/src/string/ft_strsplit.c
		libft/src/string/ft_strstr.c
		libft/src/string/ft_strsub.c
		libft/src/string/ft_strtrim.c
		libft/src/string/ft_tolower.c
		libft/src/string/ft_toupper.c
		libft/src/string/ft_strrev.c
		libft/src/string/ft_startswith.c

		libft/src/format/ft_itoa.c
		libft/src/format/ft_ultoa.c
		libft/src/format/ft_ftoa.c
		libft/src/format/ft_ftobin.c

		libft/src/list/ft_lstadd.c
		libft/src/list/ft_lstaddend.c
		libft/src/list/ft_lstdel.c
		libft/src/list/ft_lstdelone.c
		libft/src/list/ft_lstiter.c
		libft/src/list/ft_lstmap.c
		libft/src/list/ft_lstnew.c

		libft/src/math/ft_sqrt.c
		libft/src/math/ft_pow.c
		libft/src/math/ft_abs.c
		libft/src/math/ft_trig.c
		libft/src/math/ft_log.c

		libft/src/linalg/matrix.c
		libft/src/linalg/matrix_invert.c
		libft/src/linalg/matrix_arithmetic.c
		libft/src/linalg/matrix_transform.c
		libft/src/linalg/vector.c
		libft/src/linalg/vector_arithmetic.c
		libft/src/linalg/vector_transform.c

		libft/src/hash_table/hash_table.c
		libft/src/hash_table/hash_table2.c
		libft/src/hash_table/hash.c

		libft/src/ft_alloc.c
		libft/src/ft_swap.c
		libft/src/get_next_line.c
		libft/src/t_buff.c
		libft/src/endian.c
		libft/src/swatch.c
		libft/src/ft_error_exit.c

		libft/src/threading/thread.c
		libft/src/threading/thread_pool.c

		libft/src/array/array.c
		libft/src/array/arrayi.c

		libft/src/printf/ft_printf.c
		libft/src/printf/spec_parse.c
		libft/src/printf/conversion.c
		libft/src/printf/convert.c
		libft/src/printf/apply_fw.c

		mlx_glut/src/mlx.c
		mlx_glut/src/mlx_hook.c
		mlx_glut/src/mlx_image.c
		mlx_glut/src/mlx_keys.c
		)
include_directories(headers)
include_directories(libft)

include_directories(glut)
include_directories(mlx_glut)
target_link_libraries(fractol
		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/glut/freeglut.lib
		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/glut/freeglutd.lib)

#include_directories(minilibx_macos)
#target_link_libraries(fractol
#		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/libft/libft.a
#		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/minilibx_macos/libmlx.a
#		"-framework OpenGL"
#		"-framework AppKit"
#		)
