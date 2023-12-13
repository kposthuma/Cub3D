/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/13 14:00:18 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/13 16:09:47 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// static bool	horizontal_check(char *line)
// {
// 	size_t	i;
// 	bool	wall;
// 	bool	floor;

// 	i = 0;
// 	wall = false;
// 	floor = false;
// 	while (line[i] && line[i] != '\n')
// 	{
// 		if (line[i] == '1' && floor == false)
// 			wall = true;
// 		if (line[i] == '1' && floor == true)
// 		{
// 			wall = false;
// 			floor = false;
// 		}
// 		if (line[i] == '0')
// 			floor = true;
// 		if (ft_strchr(ALLOWED, line[i]) == NULL
// 			|| (floor == true && wall == false))
// 			return (false);
// 		i++;
// 		// ft_printf("pos <%s>\n", line + i);
// 	}
// 	if (floor == true)
// 		return (false);
// 	return (true);
// }

static bool	_validate_map(t_data **start)
{
	t_data	*node;

	node = *start;
	while (node != NULL)
	{
		// if (horizontal_check((char *)node->cont) == false)
		// 	return (false);
		// ft_printf("test: %s", (char *)node->cont);
		node = node->next;
	}
	return (true);
}

bool	validate_map(t_data **head)
{
	t_data	*node;

	node = *head;
	while (node->flag != MAP_START)
		node = node->next;
	return (_validate_map(&node));
}
