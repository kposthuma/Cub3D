/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 14:00:18 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/14 19:38:43 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

t_location	find_player(char **map)
{
	t_location	loc;
	size_t		i;
	size_t		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
				break ;
			j++;
		}
		i++;
	}
	loc.x = i;
	loc.y = j;
	return (loc);
}

bool	check_map(char **map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((x == 0 && map[y][x] == FLOOR) || (y == 0 && map[y][x] == FLOOR)
				|| (map[y][x] == FLOOR && map[y][x + 1] == '\0')
				|| (map[y][x] == FLOOR && map[y + 1] == NULL)
				|| (map[y][x] == FLOOR && map[y][x + 1] == ' ')
				|| (map[y][x] == FLOOR && map[y + 1][x] == ' '))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	_validate_map(char **map)
{
	if (!player(map))
		return (false);
	if (!check_map(map))
		return (false);
	return (true);
}

static size_t	determine_length(t_data **start)
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

static size_t	determine_height(t_data **start)
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

void	replace_nl(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = ' ';
		i++;
	}
}

char	**make_map(t_data *start)
{
	size_t	h;
	size_t	l;
	size_t	i;
	char	**map;

	h = determine_height(&start);
	map = ft_calloc(h, sizeof(char *));
	l = determine_length(&start);
	i = 0;
	while (start != NULL)
	{
		map[i] = ft_calloc(l, sizeof(char));
		ft_strlcpy(map[i], (char *)start->cont, l);
		replace_nl(map[i]);
		while (!map[i][l - 2])
			ft_strlcat(map[i], "            ", l);
		i++;
		start = start->next;
	}
	print_charpp(map);
	return (map);
}

bool	validate_map(t_data **head)
{
	t_data	*node;
	char	**map;

	node = *head;
	while (node->flag != MAP_START)
		node = node->next;
	map = make_map(node);
	free((char *)node->cont);
	node->cont = (void *)map;
	return (_validate_map((char **)node->cont));
}
