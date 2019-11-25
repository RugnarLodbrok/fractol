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


typedef struct
{
	t_thread thread;
	int n;
	int i;
	void (*f)(void *p, int threads_n, int threads_i);
	void *p;
} t_tpool_worker;

typedef struct
{
	int n;
	t_tpool_worker *workers;
} t_tpool;

DWORD WINAPI t_thread_func(void *p);
t_thread t_thread_create(void (*f)(void *p), void *p);
int t_thread_start(t_thread *t);
int t_thread_wait(t_thread *t, int millis);

t_tpool t_tpool_create(int n,
					   void (*f)(void *p, int threads_n, int threads_i),
					   void *p);
void t_poool_start(t_tpool *pool);

#endif
