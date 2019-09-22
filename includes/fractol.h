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

#define WTH 1000.0f
#define HGT 1000.0f
#define THR 50
#define PART HGT / THR

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

typedef struct			s_complex
{
	float 				re;
	float 				im;
}						t_complex;

typedef struct			s_color
{
	char 				r;
	char 				g;
	char				b;
}						t_color;

typedef struct			s_pnts
{
	float				x;
	float 				y;
}						t_pnts;

typedef struct			s_fcl
{
	t_complex			c;
	t_complex			min;
	t_complex			max;
	t_complex			factor;
	t_pnts				pt;
	float 				zoom_factor;
	float 				tmp1;
	float				offset1;
	float				offset2;
	int 				stop_move;
	int 				max_i;
	int					(*f)(t_complex, void *);
	t_mlx				mlx;
}						t_fcl;


typedef struct			s_thr
{
	int 				index;
	pthread_t			p;
	t_fcl				fcl;
}						t_thr;


#endif //FRACTOL_V5_FRACTOL_H
