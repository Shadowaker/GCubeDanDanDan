#include "../../incl/gcube.h"

static void	init_directions(t_game *game, char c)
{
	// N E 0.66		S W -0.66

	game->state->dirx = -1;
	game->state->diry = 0;
	game->state->angle[0] = 0;
	game->state->angle[1] = 0.66;
}

static int	hits(t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)		// if map not contained this will crash
	{
		if (game->ray->side_dist[0] < game->ray->side_dist[1])
		{
			game->ray->side_dist[0] += game->ray->delta_dist[0];
			game->ray->mapx += game->ray->step[0];
			game->ray->side = 0;
		}
		else
		{
			game->ray->side_dist[1] += game->ray->delta_dist[1];
			game->ray->mapy += game->ray->step[1];
			game->ray->side = 1;
		}
		if (game->map[game->ray->mapy][game->ray->mapx] == '1')
			hit = 1;
	}
	return (hit);
}

int	raycast(t_game *game)
{
	t_img	img;
	t_ray	ray;

	init_directions(game, 'N');

	img.img = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	ft_memset(&ray, 0, sizeof(t_ray));
	game->ray = &ray;
	game->img = &img;
	for (int x = 0; x < WIDTH; x++)
	{
		// CAST RAY --------------------------------------------------------
		game->state->camx = 2 * x / ((double)WIDTH - 1);
		game->ray->ray_dirx = game->state->dirx + (game->state->angle[0] * game->state->camx);
		game->ray->ray_diry = game->state->diry + (game->state->angle[1] * game->state->camx);
		game->ray->mapx = (int) game->state->posx;
		game->ray->mapy = (int) game->state->posy;

		if (game->ray->ray_dirx == 0)
			game->ray->delta_dist[0] = 1e30;
		else
			game->ray->delta_dist[0] = fabs(1 / game->ray->ray_dirx);

		if (game->ray->ray_diry == 0)
			game->ray->delta_dist[1] = 1e30;
		else
			game->ray->delta_dist[1] = fabs(1 / game->ray->ray_diry);

		if (game->ray->ray_dirx < 0)
		{
			game->ray->step[0] = -1;
			game->ray->side_dist[0] = (game->state->posx - game->ray->mapx) * game->ray->delta_dist[0];
		}
		else
		{
			game->ray->step[0] = 1;
			game->ray->side_dist[0] = (game->ray->mapx + 1.0 - game->state->posx) * game->ray->delta_dist[0];
		}

		if (game->ray->ray_diry < 0)
		{
			game->ray->step[1] = -1;
			game->ray->side_dist[1] = (game->state->posy - game->ray->mapy) * game->ray->delta_dist[1];
		}
		else
		{
			game->ray->step[1] = 1;
			game->ray->side_dist[1] = (game->ray->mapy + 1.0 - game->state->posy) * game->ray->delta_dist[1];
		}
		hits(game);

		if (game->ray->side == 0)
			game->ray->perp_wall_dist = ((game->ray->mapx - game->state->posx + (1 - game->ray->step[0]) / 2) / game->ray->ray_dirx);
		else
			game->ray->perp_wall_dist = ((game->ray->mapy - game->state->posy + (1 - game->ray->step[1]) / 2) / game->ray->ray_diry);
		game->ray->draw[1] = (int) (HEIGHT / game->ray->perp_wall_dist);
		game->ray->draw[0] = (-game->ray->draw[1] / 2) + (HEIGHT / 2);
		if (game->ray->draw[0] < 0)
			game->ray->draw[0] = 0;
		game->ray->draw[2] = (game->ray->draw[1] / 2) + (HEIGHT / 2);
		if (game->ray->perp_wall_dist < 0.000001)
		{
			game->ray->perp_wall_dist = 0;
			game->ray->draw[2] = HEIGHT;
		}
		if (game->ray->draw[2] >= HEIGHT)			// protect segfault
			game->ray->draw[2] = HEIGHT;
		draw_ray(game, x, game->ray->draw[0], &img);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
	return (1);
}



