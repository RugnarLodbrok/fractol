#include "threading.h"
#include "libft.h"

static void t_pool_worker_foo(t_tpool_worker *w)
{
	w->f(w->p, w->n, w->i);
}

t_tpool t_tpool_create(int n,
					   void (*f)(void *p, int threads_n, int threads_i),
					   void *p)
{
	int i;
	t_tpool pool;
	t_tpool_worker *w;

	pool.n = n;
	pool.workers = ft_memalloc(sizeof(t_tpool_worker) * n);
	i = -1;
	while (++i < n)
	{
		w = &pool.workers[i];
		ft_bzero(w, sizeof(t_tpool_worker));
		w->p = p;
		w->f = f;
		w->n = n;
		w->i = i;
		w->thread = t_thread_create(t_pool_worker_foo, w);
	}
	return pool;
}

void t_poool_start(t_tpool *pool)
{
	int i;

	i = -1;
	while (++i < pool->n)
		t_thread_start(&pool->workers[i].thread);
}
