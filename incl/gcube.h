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

# define RED "\033[31m"
# define NONE "\033[0m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define WIDTH 24
# define HEIGHT 24
# define WINDOW_W 640
# define WINDOW_H 480

# define FOV 0.66
# define PI 3.14159
# define MOVSPEED 0.1
# define ROTSPEED 0.05
# define SPEED 1

typedef struct s_game {

	void				*mlx;
	void				*mlx_win;
	char				**map;
	struct s_img		*img;
	struct s_state		*state;
	struct s_ray		*ray;
}				t_game;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// stato della telecamera (posizione, direzione, piano di proiezione)
typedef struct s_state{

	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	angle[2];
	double	camx;
}			t_state;

// informazioni sul raggio
typedef struct s_ray {

	int		mapx;
	int		mapy;
	int		side;
	int		step[2];
	int		draw[3];		// start, height, end	
	double	ray_dirx;
	double	ray_diry;
	double	perp_wall_dist;
	double	side_dist[2];
	double	delta_dist[2];
}			t_ray;

int	raycast(t_game *game);

#endif
