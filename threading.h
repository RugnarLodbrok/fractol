#ifndef THREADING_H
# define THREADING_H

# include <Windows.h>

typedef struct
{
	HANDLE handle;
	void (*f)(void *p);
	void *p;
	int is_started;
	int is_finished;
} t_thread;

DWORD WINAPI t_thread_func(void *p);
t_thread t_thread_create(void (*f)(void *p), void *p);
int t_thread_start(t_thread *t);
int t_thread_wait(t_thread *t, int millis);

#endif
