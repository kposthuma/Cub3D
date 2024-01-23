/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:04:06 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 12:42:57 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Finds the player character in a string.
 *
 * This function searches for the characters
 * 'N', 'E', 'W', or 'S' in the given string.
 * It keeps track of the number of occurrences
 * found and returns 0 if more than one player character is found.
 *
 * @param str The string to search in.
 * @param index The index of the string (unused).
 * @return Returns 1 if a single player character is found, otherwise returns 0.
 */
int	find_player(char **str)
{
	static int	found = 0;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_strchr("NEWS", str[i][j]))
			{
				if (found)
					return (0);
				found++;
			}
			j++;
		}
		i++;
	}
	// if (found == 0)
	// 	return (printf("test\n"), 0);
	return (1);
}

static bool	_check_map(char **map, size_t x, size_t y)
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
	if (map[y][x + 1] == ' ' || map[y + 1][x] == ' ' || !map[y][x + 1] || !map[y
		+ 1][x] || map[y][x - 1] == ' ' || map[y - 1][x] == ' ')
		return (false);
	return (true);
}

/**
 * @brief Checks if the given map is valid.
 *
 * This function checks if the map meets the required conditions for being valid.
 * It searches for the player's starting location and iterates through the map
 * to ensure that it is surrounded by walls and contains only valid characters.
 *
 * @param map The map to be validated.
 * @return 1 if the map is valid, 0 otherwise.
 */
int	check_map(char **map)
{
	t_location	loc;

	loc = find_loc(map, "NESW");
	while (loc.y != ft_arrlen(map))
	{
		if (loc.x == 0 || loc.y == 0)
			return (0);
		if (!_check_map(map, loc.x, loc.y))
			return (0);
		loc = find_loc(map, "0");
	}
	return (1);
}
