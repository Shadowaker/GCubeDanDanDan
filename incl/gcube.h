/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:32:03 by dridolfo          #+#    #+#             */
/*   Updated: 2023/02/15 16:41:58 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCUBE_H
# define GCUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# ifndef LIN
#  include "../mlx/mlxo/mlx.h"
# else
#  include "../mlx_linux/mlx.h"
# endif

# define RED "\033[91m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define BLUE "\033[94m"
# define PURPLE "\033[95m"
# define CYAN "\033[96m"
# define BLANK "\033[0m"

# define BUFFER_SIZE 100
# define STD_SIZE 500

# ifndef TEXT
#  define TEXT 1
# endif

# define WIDTH 24
# define HEIGHT 24
# define WINDOW_W 1280
# define WINDOW_H 960

# define MINIMAP 200
# define MINIMAP_S 10

# define FOV 60
# define PI 3.14159
# define MOVSPEED 0.04
# define ROTSPEED 0.06

# define PLAYER_R 10
# define F 0x000089AD
# define C 0x00403125

# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

# define BARREL "./srcs/sprites/test/barrel.xpm"
# define BLUESTONE "./srcs/sprites/test/bluestone.xpm"
# define COLORSTONE "./srcs/sprites/test/colorstone.xpm"
# define EAGLE "./srcs/sprites/test/eagle.xpm"
# define GREENLIGHT "./srcs/sprites/test/greenlight.xpm"
# define GREYSTONE "./srcs/sprites/test/greystone.xpm"
# define MOSSY "./srcs/sprites/test/mossy.xpm"
# define PILLAR "./srcs/sprites/test/pillar.xpm"
# define PURPLESTONE "./srcs/sprites/test/purplestone.xpm"
# define REDBRICK "./srcs/sprites/test/redbrick.xpm"
# define WOOD "./srcs/sprites/test/wood.xpm"
# define WALLE "./srcs/sprites/test/WallE.xpm"
# define WALLN "./srcs/sprites/test/WallN.xpm"
# define WALLW "./srcs/sprites/test/WallE.xpm"
# define WALLS "./srcs/sprites/test/WallS.xpm"
# define DOOR "./srcs/sprites/test/door.xpm"

# define OBJS "CPBG"

// Main game struct
typedef struct s_game {
	void				*mlx;
	void				*mlx_win;
	char				**map;
	int					map_w;
	int					map_h;
	int					minimap[2];
	int					f[3];
	int					c[3];
	struct s_img		*img;
	struct s_player		*player;
	struct s_ray		*ray;
	struct s_textures	*texts;
	struct s_object		*objs;
	struct s_object		*sorted;
}				t_game;

// Image struct
typedef struct s_img {
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
	int		lenght;
	double	dir[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	wall_dist;
}			t_ray;

// Texture memory -> Drunk Dan was here
typedef struct s_tex {
	t_img	xpm;
	int		w;
	int		h;
}			t_tex;

// Textures
typedef struct s_textures {
	t_tex	wall;
	t_tex	wall_side;
	t_tex	no;
	t_tex	so;
	t_tex	we;
	t_tex	ea;
	t_tex	door;
	t_tex	barrel;
	t_tex	column;
	t_tex	greenlight;
}			t_textures;

// Object Struct
typedef struct s_object
{
	char			type;
	int				x;
	int				y;
	double			dist;
	t_tex			*tex;
	struct s_object	*next;
	struct s_object	*sort;

}				t_object;

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

//			srcs/utils/strutils.c
size_t			ft_strlen(const char *s);
char			*str_constructor(char c, int size);

//			srcs/utils/charutils.c
void			find_char(char **map, char c, int *ids);
int				ft_isinstr(const char *stack, char c);

//			srcs/utils/ft_strcmp.c
int				ft_strcmp(char *s1, char *s2);

//			srcs/utils/ft_split.c
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(const char *s, char c);

//			srcs/utils/ft_strjoin.c
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_dotjoin(char const *s1, char const *s2, char *sep);
char			*ft_freejoin(char *s1, char *s2);

//			srcs/utils/ft_strreplace.c
char			*ft_strreplace(char const *src, char *stack, char *paste);
char			*ft_strreverse(char *str);

//			srcs/utils/gnl_utils.c
char			*ft_strmerge(char *buff, char *tmp_buff);
int				ft_find_line(char *s);
char			*ft_return_line(char *buff);

//			srcs/utils/gnl.c
char			*ft_prepare_next(char *buff);
char			*get_next_line(int fd);

//			srcs/utils/matutils.c
void			free_mat(char **mat);
void			print_mat(char **mat, char del);
int				ft_matlen(char **arr);
void			ft_cpmat(char **src, char **dst, int start);
char			**ft_matmerge(char **arr1, char **arr2);

//			srcs/utils/ft_revmat.c
char			**ft_revmat(char **mat);
//			srcs/utils/mapvalidator.c
int				map_validator(char **map);
//			srcs/utils/ft_itoa.c
int				ft_atoi(const char *str);
//			srcs/utils/absf.c
double			absf(double i);
//			srcs/utils/ft_memset.c
void			*ft_memset(void *b, int c, size_t len);
//			srcs/utils/ft_calloc.c
void			*ft_calloc(size_t count, size_t size);
//			srcs/utils/parse.c
int				parser(t_game *game, t_textures *texts, char *path);

//			srcs/utils/map.c
int				map_init(t_game *game, int fd);
void			replace_occurence_mat(char **mat, char *stack, char *paste);
char			**expand_mat(char **mat, char *str);

//			srcs/engine/textured/objects.c
t_object		*new_object(t_game *game, double dist, t_tex *tex);
t_object		*add_front_object(t_game *game, t_object **objs,
					double dist, t_tex *tex);
t_object		*add_sorted_object(t_object **sorted, t_object *obj);
void			clear_objs(t_object **objs);
t_object		*sort_objects(t_game *game);

//			srcs/engine/textured/load_textures.c
int				load_text(t_game *game, t_tex *tex, char *path);
int				load_door(t_game *game, t_tex *tex, char *path);
int				load_image(t_game *game, t_textures *texts, char *path);

//			srcs/engine/textured/rgbutility.c
unsigned long	create_rgb(int r, int g, int b);
int				get_rgb(char *addr, int x, int y);
int				load_rgb(t_game *game, char *line);

//			srcs/engine/textured/raycaster_text.c
int				raycast_text(t_game *game, t_img *img, t_ray *ray);

//			srcs/engine/textured/draw_textured.c
unsigned long	get_pixel(t_img *img, int x, int y);
void			draw_ray_text(t_ray *ray, int x, int color, t_img *img);
void			draw_crosshair(t_img *img);

//			srcs/engine/textured/load_sprites.c
int				load_sprites(t_game *game, t_textures *texts);

//			srcs/engine/textured/sprites.c
void			get_all_objects(t_game *game);

//			srcs/engine/textured/draw_sprites.c
void			draw_sprites(t_game *game, double *zbuff);

//			srcs/engine/engine.c
void			minimap(t_game *game, t_img *img);
void			engine(t_game *game, t_img *img, t_ray *ray);

//			srcs/engine/utils.c
double			deg_2_rad(double deg);

//			srcs/engine/minimap.c
void			render_minimap(t_game *game);

//			srcs/engine/minimap_utils.c
void			draw_square_border(t_img *img, int len, int offset_x,
					int offset_y);
void			draw_square(t_img *img, int len, int offset_x, int offset_y);
void			draw_black_square(t_img *img, int len, int offset_x,
					int offset_y);
void			draw_green_square(t_img *img, int len, int offset_x,
					int offset_y);

//			srcs/engine/untextured/raycaster.c
int				raycast(t_game *game, t_img *img, t_ray *ray);

//			srcs/engine/untextured/draw.c
void			my_mlx_pixel_put(t_img *data, int x, int y, unsigned int color);
void			draw_ray_minimap(t_ray *ray, int x, t_img *img);
void			draw_ray(t_ray *ray, int x, int y, t_img *img);

//			srcs/engine/untextured/dda.c
void			dda(t_game *game, t_ray *ray);

//			MISC
void			ft_sortprint(t_object *lst);
void			culo(int *i);

#endif
