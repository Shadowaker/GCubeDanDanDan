/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:45:26 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/28 10:37:29 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

// Ray infos
typedef struct s_ray {
	int		pos[2];
	int		draw[2];
	int		incr[2];
	int		ray_id;
	int		side;
	int		wall_height;
	int		lenght;
	int		texx;
	double	dir[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	wallx;
	double	step;
	double	texpos;
	double	wall_dist;
}			t_ray;

// Image struct
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// Texture data -> Drunk Dan was here
typedef struct s_tex {
	t_img	xpm;
	int		w;
	int		h;
}			t_tex;

// Animations, fp -> fireplace, de -> deatheater
typedef struct s_animations {
	t_tex	fp0;
	t_tex	fp1;
	t_tex	fp2;
	t_tex	fp3;
	t_tex	de0;
	t_tex	de1;
	t_tex	de2;
	t_tex	de3;
	t_tex	de4;
}				t_animations;

// Textures
typedef struct s_textures {
	t_tex			wall;
	t_tex			wall_side;
	t_tex			no;
	t_tex			so;
	t_tex			we;
	t_tex			ea;
	t_tex			door;
	t_tex			barrel;
	t_tex			column;
	t_tex			greenlight;
	t_animations	*ani;
}			t_textures;

// Object draw struct
typedef struct s_dsprite
{
	int				drawx[2];
	int				drawy[2];
	double			pos[2];
	double			transf[2];
	double			inv_det;
	int				spr_screen_x;
	int				spr_h;
	int				spr_w;
}				t_dsprite;

#endif
