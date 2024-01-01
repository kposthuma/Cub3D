/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/01 14:07:57 by koen          #+#    #+#                 */
/*   Updated: 2024/01/01 15:05:11 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// doesn't work for downwark angles yet D:
float	collision_left(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	x = (size_t)player->location[0];
	while (x > 0)
	{
		dx = player->location[0] - x;
		dy = tan(player->ray[i].angle) * dx;
		y = player->location[1] - dy;
		if (map[y][x - 1] == '1');
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		x--;
	}
	return (WIDTH);
}

float	collision_right(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	x = (size_t)player->location[0];
	while (x < ft_strlen(map[0]))
	{
		dx = player->location[0] - x;
		dy = tan(player->ray[i].angle) * dx;
		y = player->location[1] - dy;
		if (map[y][x] == '1');
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		x++;
	}
	return (WIDTH);
}

float	ray_len(t_player *player, size_t i, char **map)
{
	float	x;
	float	y;

	if (player->ray[i].angle < PI)
		x = collision_left();
	else
		x = collision_right();
	if (player->ray[i].angle > (PI / 2) && player->ray[i].angle < (3 * PI / 2))
		y = collision_down();
	else
		y = collision_up();
	if (x < y)
		return (x);
	else
		return (y);
}