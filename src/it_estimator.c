#include "fractol.h"

void t_ies_init(t_it_estimator *ies)
{
	ies->size = 1024;
	ies->data = malloc(sizeof(int) * ies->size);
	t_ies_reset(ies);
}

void t_ies_reset(t_it_estimator *ies)
{
	int i;

	i = -1;
	while (++i < ies->size)
		ies->data[i] = 0;
}

void t_ies_add(t_it_estimator *ies, int i)
{
	if (i >= ies->size)
		return;
	ies->data[i]++;
}

int t_ies_estimate(t_it_estimator *ies)
{
	// estimate n so that after n iterations 90% of pixels that can escape will escape
	int i;
	int size;
	int n1;
	int n2;
	int n3;
	int r;

	size = ies->size;
	while (size-- >= 0)
		if (ies->data[size])
			break; //todo: bin search
	i = 0;
	n1 = 0;
	while (i <= 1 * size / 3)
		n1 += ies->data[i++];
	n2 = n1;
	while (i <= 2 * size / 3)
		n2 += ies->data[i++];
	n3 = n2;
	while (i <= 3 * size / 3)
		n3 += ies->data[i++];
	r = n3 + (int)(((double)(n3 - n2)) / (1. - (double)(n3 - n2) / (n2 - n1)));
	r = r * 9 / 10;
	i = 0;
	n1 = 0;
	while (i <= size)
	{
		n1 += ies->data[i++];
		if (n1 > r)
		{
//			ft_printf("es:\t%d\n", i);
			return (i);
		}
	}
//	ft_printf("noes:\t%d\n", i);
	return (size);
}
