#ifndef MLX_CONSTS_H
# define MLX_CONSTS_H

# define MLX_EVENT_KEY_PRESS 2
# define MLX_EVENT_KEY_RELEASE 3
# define MLX_EVENT_EXIT 17

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_N 45
# define KEY_M 46
# define KEY_ESC 53
# define KEY_I 34
# define KEY_P 35
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_HOME 115
# define KEY_END 119

# ifdef _WIN32
#  define RED 0x1
#  define GREEN 0x100
#  define BLUE 0x10000
# else
#  define RED 0x10000
#  define GREEN 0x100
#  define BLUE 0x1
# endif
# define ALPHA 0x1000000
# define GRAYSCALE 0x010101
# define WHITE 0xffffff



#endif
