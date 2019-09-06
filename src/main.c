#include <tclDecls.h>
#include "../includes/fractol.h"

void			alert_message(char *alert)
{
	ft_putstr(alert);
}

void			init_fcl(t_fcl *fcl)
{
	fcl->mlx->mlx = mlx_init();
	fcl->mlx->win = mlx_new_window(fcl->mlx->mlx, WTH, HGT, "Fractol");
	fcl->mlx->img = mlx_new_image(fcl->mlx->mlx, WTH, HGT);
	fcl->max_i = 100;
}

void			*julia(void *thread)
{
	t_thr		*t;
	int 		i;
	int 		x;
	int 		y;

	t = (t_thr *)thread;
	y = t->index * HGT / THR;
	while (y++ < HGT / THR * (t->index + 1))
	{
		x = 0;
		while (x++ < WTH)
		{
			i =
			if (i < t->fcl->max_i)
				set_color(i, x, y, t->fcl);
		}
	}
}

void			pthread_calc(t_fcl *fcl)
{
	t_thr		*t;
	int 		i;

	i = 0;
	if ((t = (t_thr *)malloc(sizeof(t_thr) * THR)) == NULL)
		alert_message("malloc drop programme!\n");
	while (i++ < THR)
	{
		t[i].index = i;
		t[i].fcl = fcl;
		pthread_create(&(t[i].p), NULL, fcl->f, (void *)&t[i]);
	}
	while (i--)
		pthread_join(t[i].p, NULL);
	free(t);
}

void			showing(t_fcl *fcl)
{
	pthread_calc(fcl);
	mlx_put_image_to_window(fcl->mlx->mlx, fcl->mlx->win, fcl->mlx->img, 0, 0);
}

void			change_algorithm(t_fcl *fcl, char *algorithm)
{
	if (ft_strcmp("julia", algorithm) == 0)
		 fcl->f = julia;
}

int main(int argc, char *argv[])
{
	t_fcl		fcl;

	if (argc == 2)
	{
		change_algorithm(&fcl, argv[1]);
		init_fcl(&fcl);
		showing(&fcl);
	}
	return 0;
}