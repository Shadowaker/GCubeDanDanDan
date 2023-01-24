#include "../../../incl/gcube.h"

unsigned long create_rgb(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int	get_rgb(char *addr, int x, int y)
{
	int	rgb[3];

	rgb[0] = addr[(x * 4) + (y * 64 * 4) + 2];
	rgb[1] = addr[(x * 4) + (y * 64 * 4) + 1];
	rgb[2] = addr[(x * 4) + (y * 64 * 4)];
	return (0x00FFFFFF & (rgb[0] << 16 | rgb[1] << 8 | rgb[2]));
}

int	load_rgb(t_game *game, char *line)
{
	int		i;
	char	**s;
	char	**rgbb;

	s = ft_split(line, ' ');
	if (ft_matlen(s) != 2)
	{
		free_mat(s);
		return (1);
	}
	if (!ft_strcmp(s[0], "F"))
	{
		rgbb = ft_split(s[1], ',');
		if (ft_matlen(rgbb) != 3)
		{
			free_mat(s);
			free_mat(rgbb);
			return (1);
		}
		i = -1;
		while (i++ < 2)
			game->f[i] = ft_atoi(rgbb[i]);
		free_mat(rgbb);
	}
	if (!ft_strcmp(s[0], "C"))
	{
		rgbb = ft_split(s[1], ',');
		if (ft_matlen(rgbb) != 3)
		{
			free_mat(s);
			free_mat(rgbb);
			return (1);
		}
		i = -1;
		while (i++ < 2)
			game->c[i] = ft_atoi(rgbb[i]);
		free_mat(rgbb);
	}
	free_mat(s);
	return (0);
}

