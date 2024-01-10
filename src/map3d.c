/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 14:00:18 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/10 14:11:01 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	_check_map(char **map, size_t x, size_t y)
{
	map[y][x] = '1';
	if (map[y][x + 1] == '0')
	{
		if (!_check_map(map, x + 1, y))
			return (false);
	}
	if (map[y + 1][x] == '0')
	{
		if (!_check_map(map, x, y + 1))
			return (false);
	}
	if (map[y][x + 1] == ' ' || map[y + 1][x] == ' '
		|| !map[y][x + 1] || !map[y + 1][x]
		|| map[y][x - 1] == ' ' || map[y - 1][x] == ' ' )
		return (false);
	return (true);
}

bool	check_map(char **map)
{
	t_location	loc;

	loc = find_loc(map, "NESW");
	while (loc.y != strofstrlen(map))
	{
		if (loc.x == 0 || loc.y == 0)
			return (false);
		if (!_check_map(map, loc.x, loc.y))
			return (false);
		loc = find_loc(map, "0");
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
		trim_nl(map[i]);
		while (!map[i][l - 2])
			ft_strlcat(map[i], "            ", l);
		i++;
		start = start->next;
	}
	return (map);
}

bool	validate_map(t_data **head)
{
	t_data	*node;
	char	**map;

	node = find_node(head, MAP_START);
	map = make_map(node);
	// print_charpp(map);
	if (!_validate_map(map))
		return (ft_free(map), false);
	ft_free(map);
	map = make_map(node);
	free((char *)node->cont);
	node->cont = (void *)map;
	return (true);
}
