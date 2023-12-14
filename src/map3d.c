/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 14:00:18 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/14 13:53:50 by kposthum      ########   odam.nl         */
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

static bool	_validate_map(char **map)
{
	if (!player(map))
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
