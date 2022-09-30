/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:32:03 by dridolfo          #+#    #+#             */
/*   Updated: 2022/09/30 17:58:12 by dridolfo         ###   ########.fr       */
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

# define RED "\033[31m"
# define NONE "\033[0m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define PURPLE "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BUFFER_SIZE 100

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
	int					tmp;
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

int		raycast(t_game *game);
void	draw_ray(t_game *game, int x, int y, t_img *img);

#endif
