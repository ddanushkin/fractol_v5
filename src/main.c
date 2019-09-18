#include "../includes/fractol.h"

void			alert_message(char *alert)
{
	ft_putstr(alert);
}

void			init_fcl(t_fcl *fcl)
{
	fcl->mlx.mlx = mlx_init();
	fcl->mlx.win = mlx_new_window(fcl->mlx.mlx, WTH, HGT, "Fractol");
//	fcl->mlx.img = mlx_new_image(fcl->mlx.mlx, WTH, HGT);
	fcl->max_i = 100;
}

//float 			color_func(int it, float off)
//{
//	float		res;
//
//	res = (float)cos(sqrt(it) + off);
//	return (255 * res * res);
//}

void			pixel_to_img(t_fcl *f, int x, int y, t_color c)
{
	int 		index;

	index = x * 4 + f->mlx.sl * y;
	f->mlx.data[index] = (char)c.b;
	f->mlx.data[index + 1] = (char)c.g;
	f->mlx.data[index + 2] = (char)c.r;
}

void			set_color(float iter, float x, float y, t_fcl *f)
{
	t_color		color;
	float 		t;

	t = iter / (float) f->max_i;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (iter < f->max_i)
	{
		color.r = (9 * (1 - t) * t * t * t * 255);
		color.g = (15 * (1 - t) * (1 - t) * t * t * 255);
		color.b = (8.5f * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	pixel_to_img(f, x, y, color);
}

//void			*julia(void *thread)
//{
//	t_thr		*t;
//	float 		i;
//	int 		x;
//	int 		y;
//	float		c_re;
//	float 		c_im;
//	float 		new_re;
//	float 		new_im;
//	float 		old_re;
//	float 		old_im;
//
//	float 		zoom = 1.0f;
//	float 		move_x = 0.0f;
//	float		move_y = 0.0f;
//
//	c_re = -0.7f;
//	c_im = 0.27015f;
//
//	t = (t_thr *)thread;
//	y = t->index * HGT / THR;
//	while (y < HGT / THR * (t->index + 1))
//	{
//		x = 0;
//		while (x < WTH)
//		{
//			i = 0.0f;
//			new_re = 1.5f * (x - WTH / 2.0f) / (0.5f * zoom * WTH) + move_x;
//			new_im = (y - HGT / 2.0f) / (0.5f * zoom * HGT) + move_y;
//			while (i < t->fcl->max_i)
//			{
//				old_re = new_re;
//				old_im = new_im;
//				new_re = old_re * old_re - old_im * old_im + c_re;
//				new_im = 2.0f * old_re * old_im + c_im;
//				if ((new_re * new_re + new_im * new_im) > 4)
//					break ;
//			}
//			if (i < t->fcl->max_i)
//				set_color(i, x, y, t->fcl);
//			x++;
//		}
//		y++;
//	}
//	return (NULL);
//}

int				julia(int x, int y, t_fcl *f)
{
	int 		iter;
	float		c_re;
	float 		c_im;
	float 		x_temp;
	float 		y_temp;

	iter = 0;
	f->pt.x = WTH / HGT * (x - WTH / 2) / (WTH / 2);
	f->pt.y = (y - HGT / 2) / (HGT / 2);
	c_re = -0.7f;
	c_im = 0.27015f;
	while (f->pt.x * f->pt.x + f->pt.y * f->pt.y <= 4.0f && iter < f->max_i)
	{
		x_temp = f->pt.x * f->pt.x - f->pt.y * f->pt.y + c_re;
		y_temp = 2 * f->pt.x * f->pt.y + c_im;
		f->pt.x = x_temp;
		f->pt.y = y_temp;
		iter++;
	}
	return (iter);
}

void			*fractals(void *thread)
{
	t_thr		*t;
	int 		x;
	int 		y;
	int			iter;

	t = thread;
	y = t->index * HGT / THR;
	while (y < HGT / THR * (t->index + 1))
	{
		x = 0;
		while (x < WTH)
		{
			iter = julia(x, y, &t->fcl);
			if (iter < t->fcl.max_i)
				set_color(iter, x, y, &t->fcl);
			x++;
		}
		y++;
	}
	return (NULL);
}

void			pthread_calc(t_fcl *fcl)
{
	t_thr		*t;
	int 		i;

	i = 0;
	if ((t = (t_thr *)malloc(sizeof(t_thr) * THR)) == NULL)
		alert_message("malloc drop programme!\n");
	while (i < THR)
	{
		t[i].index = i;
		t[i].fcl = *fcl;
		pthread_create(&(t[i].p), NULL, fractals, (void *)&t[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i].p, NULL);
	free(t);
}

void			showing(t_fcl *f)
{
	f->mlx.img = mlx_new_image(f->mlx.mlx, WTH, HGT);
	f->mlx.data = mlx_get_data_addr(f->mlx.img, &(f->mlx.bpp), &(f->mlx.sl), &(f->mlx.endian));
	pthread_calc(f);
	mlx_clear_window(f->mlx.mlx, f->mlx.win);
	mlx_put_image_to_window(f->mlx.mlx, f->mlx.win, f->mlx.img, 0, 0);
}

void			change_algorithm(t_fcl *fcl, char *algorithm)
{
	if (ft_strcmp("julia", algorithm) == 0)
		 fcl->f = julia;
}

int 			deal_key(int key, t_fcl *f)
{
	if (key == 53)
		exit(0);
	showing(f);
	return (0);
}

int 			main(int argc, char *argv[])
{
	t_fcl		fcl;

	if (argc == 2)
	{
		change_algorithm(&fcl, argv[1]);
		init_fcl(&fcl);
		showing(&fcl);
		mlx_hook(fcl.mlx.win, 2, 5, deal_key, &fcl);
		mlx_loop(fcl.mlx.mlx);
	}
	return 0;
}