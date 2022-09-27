/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:32:03 by dridolfo          #+#    #+#             */
/*   Updated: 2022/09/27 12:47:55 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCUBE_H
# define GCUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

#define W 24
#define H 24
#define WINDOW_W 640
#define WINDOW_H 480

#define FOV 0.66
#define PI 3.14159
#define MOVSPEED 0.1
#define ROTSPEED 0.05

typedef struct s_game {

	void				*mlx;
	void				*mlx_win;
	char				**map;
	struct	s_state		*state;
}				t_game;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// stato della telecamera (posizione, direzione, piano di proiezione)
typedef struct s_state
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	camx;
	double	camy;
}			t_state;

// informazioni sul raggio
typedef struct s_rayhit
{
	double	distance;
	int		mapX;
	int		mapY;
	double	rayDirX;
	double	rayDirY;
	int		side;
}			t_rayhit;

#endif
