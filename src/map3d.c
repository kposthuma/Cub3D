/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 14:00:18 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/11 23:06:07 by root          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

	for (int bla = 0; map[bla]; bla++)
		printf("MKMAP: %s\n", map[bla]);
	return (map);
}

bool	validate_map(t_data **head)
{
	t_data	*node;
	char	**map;

	node = find_node(head, MAP_START);
	map = make_map(node);
	if (!_validate_map(map))
		return (ft_free(map), false);
	ft_free(map);
	map = make_map(node);
	free((char *)node->cont);
	node->cont = (void *)map;
	return (true);
}
