#include "../includes/fractol.h"


t_complex		init_complex(float re, float im)
{
	t_complex	c;

	c.im = im;
	c.re = re;
	return (c);
}

void			alert_message(char *alert)
{
	ft_putstr(alert);
}

void			apply_zoom(t_fcl *f, t_complex mouse)
{
	float 		interpolation;

	interpolation = 1.0f / f->zoom_factor;
	f->min.re = mouse.re + (f->min.re - mouse.re) * interpolation;
	f->min.im = mouse.im + (f->min.im - mouse.im) * interpolation;
	f->max.re = mouse.re + (f->min.re - mouse.re) * interpolation;
	f->max.im = mouse.im + (f->min.im - mouse.im) * interpolation;
	f->factor = init_complex((f->max.re - f->min.re) / (WTH - 1.0f),
							 (f->max.im - f->min.im) / (HGT - 1.0f));
	f->tmp1 = (f->max.re - f->min.re) * 0.025f;
}

void			init_fcl(t_fcl *fcl)
{
	fcl->mlx.mlx = mlx_init();
	fcl->mlx.win = mlx_new_window(fcl->mlx.mlx, WTH, HGT, "Fractal");
	fcl->max_i = 100;
	fcl->zoom_factor = 1.0f;
	fcl->stop_move = 1;
	fcl->tmp1 = 0.5f;
	fcl->offset1 = 0.0f;
	fcl->offset2 = 0.0f;
	fcl->min = init_complex(-2.0f * HGT / WTH, -2.0f);
	fcl->max.re = 2.0f * HGT / WTH;
	fcl->max.im = fcl->min.im + (fcl->max.re - fcl->min.re) * HGT / WTH;
	fcl->factor = init_complex((fcl->max.re - fcl->min.re) / (WTH - 1.0f),
							   (fcl->max.im - fcl->min.im) / (HGT - 1.0f));

}

void			pixel_to_img(t_fcl *f, float x, float y, t_color c)
{
	int 		index;

	index = (int)(x * 4.0f + f->mlx.sl * y);
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
		color.r = (char)(9 * (1 - t) * t * t * t * 255);
		color.g = (char)(15 * (1 - t) * (1 - t) * t * t * 255);
		color.b = (char)(8.5f * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	pixel_to_img(f, x, y, color);
}

//float			julia(float x, float y, void *fr)
//{
//	float 		iter;
//	float 		x_temp;
//	float 		y_temp;
//
//	t_fcl *f = (t_fcl *)fr;
//	iter = 0;
////	f->pt.x = WTH / HGT * (x - WTH * 0.5f) / (f->zoom_factor * WTH * 0.5f);
////	f->pt.y = (y - HGT * 0.5f) / (f->zoom_factor * HGT * 0.5f);
//	f->pt.x = (WTH / HGT * (x - WTH * 0.5f) / (WTH * 0.5f));
//	f->pt.y = ((y - HGT * 0.5f) / (HGT * 0.5f));
////	f->c.im = (f->max.im - x * f->factor.im);
////	f->c.re = (f->min.re - y * f->factor.re);
//	while (f->pt.x * f->pt.x + f->pt.y * f->pt.y <= 4.0f && iter < f->max_i)
//	{
//		x_temp = f->pt.x * f->pt.x - f->pt.y * f->pt.y + f->c.re;
//		y_temp = 2.0f * f->pt.x * f->pt.y + f->c.im;
//		f->pt.x = x_temp;
//		f->pt.y = y_temp;
//		iter++;
//	}
//	return (iter);
//}

int 			julia(t_complex c, void *f_)
{
	int 		i;
	t_complex	z;
	t_fcl		*f;

	z = c;
	f = (t_fcl *)f_;
	i = 0;
	while (z.re * z.re + z.im * z.im <= 4.0f && i < f->max_i)
	{
		z = init_complex(z.re * z.re + z.im * z.im + f->c.re,
				2.0f * z.re * z.im + f->c.im);
		i++;
	}
	return (i);
}

void			*fractals(void *thread)
{
	t_thr		*t;
	float 		x;
	float 		y;
	float		iter;
	t_complex	c;

	t = (t_thr *)thread;
	y = t->index * PART;
	while (y < PART * (float)(t->index + 1))
	{
		x = 0;
		c.im = (t->fcl.max.im + t->fcl.offset2 - y * t->fcl.factor.im);
		while (x < WTH)
		{
			c.re = (t->fcl.min.re + t->fcl.offset1 + x * t->fcl.factor.re);
			if ((iter = t->fcl.f(c, &(t->fcl))) < t->fcl.max_i)
				set_color(iter, x, y, &(t->fcl));
			x++;
		}
		y++;
	}
	return (NULL);
}

void			pthread_calc(t_fcl *f)
{
	t_thr		*t;
	int 		i;

	i = 0;
	if ((t = (t_thr *)malloc(sizeof(t_thr) * THR)) == NULL)
		alert_message("malloc drop programme!\n");
	while (i < THR)
	{
		t[i].index = i;
		t[i].fcl = *f;
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

int 			mouse_move(int x_, int y_, t_fcl *f)
{
	float		x;
	float 		y;

	x = (float)x_;
	y = (float)y_;
	if (f->stop_move == 0)
		return (0);
	if (x < 0 || x > WTH)
		x = (x > WTH) ? WTH : 0;
	if (y < 0 || y > HGT)
		y = (y > HGT) ? HGT : 0;
	f->c = init_complex((x - WTH * 0.5f) / WTH,
			4.0f * ((HGT - y) - HGT * 0.5f) / HGT);
	showing(f);
	return (0);
}

int 			choose_zoom(t_fcl *f, float x, float y, int key)
{
	t_complex	mouse;
	if (key == 4)
	{
		f->zoom_factor *= 1.25f;
		mouse = init_complex(x / (WTH / (f->max.re - f->min.re)) + f->min.re,
							 y / (HGT / (f->max.im - f->min.im)) + f->min.im);
		apply_zoom(f, mouse);
	}
	if (key == 5)
	{
		f->zoom_factor *= 0.8f;
		if (f->min.im == -2.0f && f->min.re == -2.0f && f->max.im == 2.0f && f->max.re == 2.0f)
			return (0);
		mouse = init_complex(x / (WTH / (f->max.re - f->min.re)) + f->min.re,
							 y / (HGT / (f->max.im - f->min.im)) + f->min.im);
		apply_zoom(f, mouse);
	}
	return (1);
}

int 			deal_mouse(int key, int x_, int y_, t_fcl *f)
{
	float		y;
	float 		x;

	y = (float)y_;
	x = (float)x_;
	y = HGT - y;
	if (key == 1)
	{
		f->max_i += 40;
	}
	if (key == 2)
	{
		f->max_i -= 40;
	}
	if (key == 4 || key == 5)
		if (choose_zoom(f, x, y, key) == 0)
			return (0);
	showing(f);
	printf("scroll down %d zoom factor %f c_re %f  c_im %f \n", key, f->zoom_factor, f->c.re, f->c.im);
	return (0);
}

int 			deal_key(int key, t_fcl *f)
{
	if (key == 123) // left
		f->offset1 += f->tmp1;
	if (key == 124) // right
		f->offset1 -= f->tmp1;
	if (key == 126) // up
		f->offset2 += f->tmp1;
	if (key == 125) // down
		f->offset2 -= f->tmp1;
	if (key == 6)
		f->stop_move = (f->stop_move == 1) ? 0 : 1;
	if (key == 53)
		exit(0);
	printf("offset1 %f offset2 %f tmp %f \n", f->offset1, f->offset2, f->tmp1);
	showing(f);
	return (0);
}

int 			main(int argc, char *argv[])
{
	t_fcl		f;

	if (argc == 2)
	{
		change_algorithm(&f, argv[1]);
		init_fcl(&f);
		showing(&f);
		mlx_hook(f.mlx.win, 2, 5, deal_key, &f);
		mlx_hook(f.mlx.win, 6, 0, mouse_move, &f);
		mlx_hook(f.mlx.win, 4, 5, deal_mouse, &f);
		mlx_loop(f.mlx.mlx);
	}
	return 0;
}