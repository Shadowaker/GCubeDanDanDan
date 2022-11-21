/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:32:03 by dridolfo          #+#    #+#             */
/*   Updated: 2022/11/21 14:40:28 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCUBE_H
# define GCUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlxo/mlx.h"

# define RED "\033[91m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define BLUE "\033[94m"
# define PURPLE "\033[95m"
# define CYAN "\033[96m"
# define BLANK "\033[0m"

# define BUFFER_SIZE 100
# define STD_SIZE	500
# define TEXT 0

# define WIDTH 24
# define HEIGHT 24
# define WINDOW_W 1280
# define WINDOW_H 960

# define MINIMAP 200
# define MINIMAP_S 10

# define FOV 60
# define PI 3.14159
# define MOVSPEED 0.03
# define ROTSPEED 0.06

# define PLAYER_R 4

# define BARREL "../srcs/sprites/test/barrel.xpm"
# define BLUESTONE "../srcs/sprites/test/bluestone.xpm"
# define COLORSTONE "../srcs/sprites/test/colorstone.xpm"
# define EAGLE "../srcs/sprites/test/eagle.xpm"
# define GREENLIGHT "../srcs/sprites/test/greenlight.xpm"
# define GREYSTONE "../srcs/sprites/test/greystone.xpm"
# define MOSSY "../srcs/sprites/test/mossy.xpm"
# define PILLAR "../srcs/sprites/test/pillar.xpm"
# define PURPLESTONE "../srcs/sprites/test/purplestone.xpm"
# define REDBRICK "../srcs/sprites/test/redbrick.xpm"
# define WOOD "../srcs/sprites/test/wood.xpm"

// Main game struct
typedef struct s_game {

	void				*mlx;
	void				*mlx_win;
	char				**map;
	int					minimap[2];
	int					map_w;
	int					map_h;
	struct s_img		*img;
	struct s_player		*player;
	struct s_ray		*ray;
	struct s_textures	*texts;
}				t_game;

// Image struct
typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

// Camera infos (position, direction, projection plane)
typedef struct s_player{
	double	cam_side;
	double	pos[2];
	double	dir[2];
	double	cam_plane[2];
}			t_player;

// Ray infos
typedef struct s_ray {
	int		pos[2];
	int		draw[2];
	int		incr[2];
	int		ray_id;
	int		side;
	int		wall_height;
	double	dir[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	wall_dist;
}			t_ray;

// Texture memory
typedef struct s_tex {
	t_img	xpm;
	int		w;
	int		h;
	int		*rgb[3];		// meh
}			t_tex;

typedef struct s_textures {
	t_tex	*wall;
	t_tex	*wall_side;
}			t_textures;

//			STRING UTILS
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);
char	*ft_freejoin(char *s1, char *s2);
char	*ft_strreplace(char const *src, char *stack, char *paste);

//			GNL
int			ft_find_line(char *s);
char		*ft_strmerge(char *buff, char *tmp_buff);
char		*ft_return_line(char *buff);
char		*ft_prepare_next(char *buff);
char		*get_next_line(int fd);
char		*ft_recover(int fd, char *buff);

//			MATRIX UTILS
char		**ft_matmerge(char **arr1, char **arr2);
void		ft_cpmat(char **src, char **dst, int start);
int			ft_matlen(char **arr);
void		free_mat(char **mat);
void		print_mat(char **mat);

//			UTILS
void	*ft_memset(void *b, int c, size_t len);
void	culo();
int		isincircle(int cx, int cy, int x, int y);
double	absf(double i);
void	*ft_calloc(size_t count, size_t size);

//			INIT
char	**map_init(char *path);
void	init_directions(t_game *game, char c);
void	load_images(t_game *game);

//			ENGINE
void	engine(t_game *game, t_img *img, t_ray *ray);
int		raycast(t_game *game, t_img *img, t_ray *ray);
double	deg_2_rad(double deg);
void	draw_ray(t_ray *ray, int x, int y, t_img *img);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_square(t_img *img, int len, int offset_x, int offset_y);
void	draw_minimap(t_game *game, t_img *img);
void	draw_ray_minimap(t_ray *ray, int x, t_img *img);

#endif
