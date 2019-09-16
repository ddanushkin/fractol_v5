//
// Created by Dremora lord Gorold goodbrother on 06/09/2019.
//

#ifndef FRACTOL_V5_FRACTOL_H
# define FRACTOL_V5_FRACTOL_H
# include <stdio.h>
#include "../libft/includes/libft.h"
#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include "pthread.h"

#define WTH 600
#define HGT 600
#define THR 50

typedef struct			s_mlx
{
	int					sl;
	int					bpp;
	int					endian;
	char 				*data;
	void				*mlx;
	void				*img;
	void				*win;
}						t_mlx;

typedef struct			s_color
{
	float 				r;
	float 				g;
	float				b;
}						t_color;

typedef struct			s_pnts
{
	float				x;
	float 				y;
}						t_pnts;

typedef struct			s_fcl
{
	t_pnts				p;
	int 				max_i;
	void				*(*f)(void *);
	t_mlx				mlx;
}						t_fcl;


typedef struct			s_thr
{
	int 				index;
	pthread_t			p;
	t_fcl				*fcl;
}						t_thr;


#endif //FRACTOL_V5_FRACTOL_H
