#include "../../incl/gcube.h"


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
		if (game->map[game->ray->mapx][game->ray->mapy] == '1')
			hit = 1;
	}
	return (hit);
}

int	raycast(t_game *game, t_img *img, t_ray *ray)
{
	game->ray = ray;
	game->img = img;
	for (int x = 0; x < WINDOW_W; x++)
	{
		// CAST RAY --------------------------------------------------------
		game->state->camx = 2 * ((double) x) / ((double) WINDOW_W - 1);
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
			game->ray->perp_wall_dist = (game->ray->side_dist[0] - game->ray->delta_dist[0]);
		else
			game->ray->perp_wall_dist = (game->ray->side_dist[1] - game->ray->delta_dist[1]);
		game->ray->draw[1] = (int) (WINDOW_H / game->ray->perp_wall_dist);
		game->ray->draw[0] = (-game->ray->draw[1] / 2) + (WINDOW_H / 2);
		game->ray->draw[2] = (game->ray->draw[1] / 2) + (WINDOW_H / 2);
		if (game->ray->draw[0] < 0)
			game->ray->draw[0] = 0;
		if (game->ray->perp_wall_dist < 0)
		{
			game->ray->perp_wall_dist = 0;
			game->ray->draw[2] = WINDOW_H;
		}
		if (game->ray->draw[2] >= WINDOW_H)			// protect segfault
			game->ray->draw[2] = WINDOW_H - 1;

		draw_ray(game, x, game->ray->draw[0], img);
	}
	return (1);
}



