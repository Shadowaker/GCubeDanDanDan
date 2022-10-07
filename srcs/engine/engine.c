#include "../../incl/gcube.h"

double	deg_2_rad(double deg)
{
	return (PI * deg / 180);
}

void	draw_minimap_ray(t_ray *ray, t_img *img)
{
	int	t;

	t = 0;
	while (t < ray->dist)
	{
		my_mlx_pixel_put(img, (ray->x * 20) + 10, (ray->y * 20) + 10, 0x00a42cd6);
		t++;
	}
}

int	raycast(t_game *game, t_img *img, t_ray *ray)
{
	unsigned int	i;
	unsigned int	wall;

	ray->ang = game->player->angle - game->player->half_fov;
	ray->incr_ang = game->player->fov / WINDOW_W;
	i = 0;
	while (i < WINDOW_W)
	{
		ray->x = game->player->posx;
		ray->y = game->player->posy;
		ray->cos = cosf(deg_2_rad(ray->ang)) / 64;
		ray->sin = sinf(deg_2_rad(ray->ang)) / 64;

		wall = 0;
		while (wall == 0)
		{
			ray->x += ray->cos;
			ray->y += ray->sin;
			if (game->map[(int) ray->y][(int) ray->x] == '1')
				wall = 1;
		}
		ray->dist = sqrtf(powf(game->player->posx - ray->x, 2.0) + powf(game->player->posy - ray->y, 2.0));
		ray->wall_height = ((int) ((WINDOW_H / 2) / ray->dist));
		
		if (i < 10 || i >= 210)
			draw_ray(ray, i, 0, img);
		else
			draw_ray_minimap(ray, i, img);
		draw_minimap_ray(ray, img);
		ray->ang += ray->incr_ang;
		i++;
	}
	return (0);
}
