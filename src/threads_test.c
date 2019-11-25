#include "libft.h"
#include "threading.h"

static void foo(char *s)
{
	ft_printf("hello from thread: `%s`1\n", s);
	_sleep(400);
	ft_printf("hello from thread: `%s`2\n", s);
}

void threads_test()
{
	t_thread t;
	t = t_thread_create(foo, "abc");
	t_thread_start(&t);
	t_thread_wait(&t, 1000);
}

