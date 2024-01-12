#include "cub3d.h"

bool	player(char **map)
{
	size_t	i;
	size_t	j;
	size_t	p;

	i = 0;
	p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
				p++;
			j++;
		}
		i++;
	}
	if (p != 1)
		return (false);
	return (true);
}

t_location	find_loc(char **map, char *arr)
{
	t_location	loc;

	loc.y = 0;
	while (map[loc.y])
	{
		loc.x = 0;
		while (map[loc.y][loc.x])
		{
			if (strchr(arr, map[loc.y][loc.x]) != NULL)
				return (loc);
			loc.x++;
		}
		loc.y++;
	}
	return (loc);
}

size_t	determine_length(t_data **start)
{
	size_t	l;
	t_data	*node;

	node = *start;
	l = 0;
	while (node != NULL)
	{
		if (ft_strlen((char *)node->cont) > l)
			l = ft_strlen((char *)node->cont);
		node = node->next;
	}
	return (l + 1);
}

size_t	determine_height(t_data **start)
{
	size_t	h;
	t_data	*node;

	node = *start;
	h = 0;
	while (node != NULL)
	{
		h++;
		node = node->next;
	}
	return (h + 1);
}
