#include "threading.h"

DWORD WINAPI t_thread_func(void *p)
{
	t_thread *t;

	t = p;
	t->f(t->p);
	return (0);
}

t_thread t_thread_create(void (*f)(void *p), void *p)
{
	t_thread t;
	t.handle = 0;
	t.is_started = 0;
	t.is_finished = 0;
	t.f = f;
	t.p = p;
	return (t);
}

int t_thread_start(t_thread *t)
{
	t->handle = CreateThread(
			NULL,
			0,
			t_thread_func,
			t,
			0,
			NULL);
	if (t->handle)
		t->is_started = 1;
	return t->is_started;
}

int t_thread_wait(t_thread *t, int millis)
{
	DWORD ret;

	ret = WaitForSingleObject(t->handle, millis);
	if (ret == WAIT_TIMEOUT)
		return 0;
	return 1;
}
