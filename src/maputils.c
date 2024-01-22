/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maputils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:08:08 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/22 16:46:58 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_location	find_loc(char **map, char *arr)
{
	t_location	loc;

	loc.y = 0;
	while (map[loc.y])
	{
		loc.x = 0;
		while (map[loc.y][loc.x])
		{
			if (ft_strchr(arr, map[loc.y][loc.x]) != NULL)
				return (loc);
			loc.x++;
		}
		loc.y++;
	}
	return (loc);
}
