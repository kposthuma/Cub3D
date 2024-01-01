/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/01 14:07:57 by koen          #+#    #+#                 */
/*   Updated: 2024/01/01 17:07:16 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
		if (player->ray[i].angle > (3 * PI / 2))
		{
			dy = tan(player->ray[i].angle) * dx;
			y = player->location[1] - dy;
		}
		else
		{
			dy = dx / tan(player->ray[i].angle);
			y = player->location[1] + dy;
		}
		if (map[y][x - 1] == '1')
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
		if (player->ray[i].angle < (PI / 2))
		{
			dy = tan(player->ray[i].angle) * dx;
			y = player->location[1] - dy;
		}
		else
		{
			dy = dx / tan(player->ray[i].angle);
			y = player->location[1] + dy;
		}
		if (map[y][x] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		x++;
	}
	return (WIDTH);
}

float	collision_down(t_player *player, size_t i, char **map)
{

	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	y = (size_t)player->location[0];
	while (y < strofstrlen(map))
	{
		dy = player->location[0] - y;
		if (player->ray[i].angle > PI)
		{
			dx = tan(player->ray[i].angle) * dy;
			x = player->location[1] - dx;
		}
		else
		{
			dx = dy / tan(player->ray[i].angle);
			x = player->location[1] + dx;
		}
		if (map[y][x] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		y++;
	}
	return (HEIGHT);
}

float	collision_up(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	y = (size_t)player->location[0];
	while (y > 0)
	{
		dy = player->location[0] - y;
		if (player->ray[i].angle > PI)
		{
			dx = tan(player->ray[i].angle) * dy;
			x = player->location[1] - dx;
		}
		else
		{
			dx = dy / tan(player->ray[i].angle);
			x = player->location[1] + dx;
		}
		if (map[y -1][x] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		y--;
	}
	return (HEIGHT);
}

float	ray_len(t_player *player, size_t i, char **map)
{
	float	x;
	float	y;

	if (player->ray[i].angle == 0 || player->ray[i].angle == PI)
		x = WIDTH;
	else if (player->ray[i].angle > PI)
		x = collision_left(player, i, map);
	else
		x = collision_right(player, i, map);
	if (player->ray[i].angle == (PI / 2)
		|| player->ray[i].angle == (3 * PI / 2))
		y = HEIGHT;
	else if (player->ray[i].angle > (PI / 2)
		&& player->ray[i].angle < (3 * PI / 2))
		y = collision_down(player, i, map);
	else
		y = collision_up(player, i, map);
	if (x < y)
		return (x);
	else
		return (y);
}
