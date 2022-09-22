/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:32:03 by dridolfo          #+#    #+#             */
/*   Updated: 2022/09/22 16:38:27 by dridolfo         ###   ########.fr       */
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
#define DISPLAY_W 640
#define DISPLAY_H 480

typedef struct s_game {

	void				*mlx;
	void				*mlx_win;
	char				**map;
	struct	s_player	*player;
}		t_game;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player {
	int	*pos;	// [posX, posY]
	int *dir;	// [dirX, dirY]
}		t_player;


#endif
