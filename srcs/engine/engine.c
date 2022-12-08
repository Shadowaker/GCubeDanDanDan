/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:30:32 by dridolfo          #+#    #+#             */
/*   Updated: 2022/12/08 15:59:30 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/gcube.h"

static void	fill_char(char *str, char c, int start, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		str[start + i] = c;
}

char	**map_for_mini(t_game *game)
{
	int		pl[2];
	int		iter[2];
	char	**res;

	pl[0] = (int) game->player->pos[0];
	pl[1] = (int) game->player->pos[1];

	int i;

	i = 0;
	res = malloc(sizeof(char *) * 21);
	while (i < 21)
		res[i++] = ft_calloc(1, 21);

	if (pl[1] - 10 < 0)
		iter[1] = 0;
	else
		iter[1] = pl[1] - 10;

	int	j;

	i = 0;
	while (game->map[iter[1]] && iter[1] < pl[1] + 10)
	{
		if (pl[0] - 10 < 0)
			iter[0] = 0;
		else
			iter[0] = pl[0] - 10;
		j = 0;
		while (game->map[iter[1]][iter[0]] && iter[0] < pl[0] + 10)
			res[i][j++] = game->map[iter[1]][iter[0]++];
		if (iter[0] < pl[0] + 10)
			fill_char(res[i], ' ', iter[0], pl[0] + 10 - iter[0]);
		iter[1]++;
		i++;
	}
	res[i] = NULL;
	return (res);
}

double	deg_2_rad(double deg)
{
	return (PI * deg / 180);
}

void	draw_minimap_ray(t_ray *ray, t_game *game, t_img *img)
{
	int		pixels;
	double	dx;
	double	dy;
	double	px;
	double	py;

	dx = (ray->pos[0] - game->player->pos[0]) / ray->delta_dist[0];
	dy = (ray->pos[1] - game->player->pos[1]) / ray->delta_dist[1];
	px = game->player->pos[0] * 20;
	py = game->player->pos[1] * 20;
	pixels = (int) (1);	// meh
	while (pixels)
	{
		my_mlx_pixel_put(img, px + 10, py + 10, 0x00D11131);
		px += dx;
		py += dy;
		pixels--;
	}
}

void	engine(t_game *game, t_img *img, t_ray *ray)
{
	char **mini;

	raycast(game, img, ray);
	mini = map_for_mini(game);
	print_mat(mini, '@');
	printf("\n\n");
	//draw_minimap(game, img);
}
