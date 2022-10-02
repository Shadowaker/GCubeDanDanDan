/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:32:03 by dridolfo          #+#    #+#             */
/*   Updated: 2022/10/02 17:11:48 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCUBE_H
# define GCUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

# define RED "\033[91m"
# define GREEN "\033[92m"
# define YELLOW "\033[93m"
# define BLUE "\033[94m"
# define PURPLE "\033[95m"
# define CYAN "\033[96m"
# define BLANK "\033[0m"

# define BUFFER_SIZE 100

# define WIDTH 24
# define HEIGHT 24
# define WINDOW_W 1280
# define WINDOW_H 960

# define FOV 0.66
# define PI 3.14159
# define MOVSPEED 0.2
# define ROTSPEED 0.03

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

//			STRING UTILS
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(const char *s, char c);

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

//			INIT
char	**map_init(char *path);
static void	init_directions(t_game *game, char c);

int		raycast(t_game *game);
void	draw_ray(t_game *game, int x, int y, t_img *img);

#endif
