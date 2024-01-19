/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:05:36 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/19 01:48:53 by root          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	collision_left(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	x = (size_t)(player->location[0] / (float)BLOCKSIZE);
	while (x > 0)
	{
		dx = (player->location[0] - x * BLOCKSIZE);
		dy = (dx * tan(player->ray[i].angle));
		if (player->ray[i].angle > PI)
			y = (size_t)((player->location[1] - fabs(dy)) / (float)BLOCKSIZE);
		else
			y = (size_t)((player->location[1] + fabs(dy)) / (float)BLOCKSIZE);
		if (y >= ft_arrlen(map))
			break ;
		if (map[y][x - 1] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		x--;
	}
	return (FLT_MAX);
}

float	collision_right(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	x = (size_t)(player->location[0] / (float)BLOCKSIZE) + 1;
	while (x < ft_strlen(map[0]))
	{
		dx = (player->location[0] - x * BLOCKSIZE);
		dy = (dx * tan(player->ray[i].angle));
		if (player->ray[i].angle > PI)
			y = (size_t)((player->location[1] - fabs(dy)) / (float)BLOCKSIZE);
		else
			y = (size_t)((player->location[1] + fabs(dy)) / (float)BLOCKSIZE);
		if (y >= ft_arrlen(map))
			break ;
		if (map[y][x] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		x++;
	}
	return (FLT_MAX);
}

float	collision_down(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	y = (size_t)(player->location[1] / (float)BLOCKSIZE) + 1;
	while (y < ft_arrlen(map))
	{
		dy = (player->location[1] - y * BLOCKSIZE);
		dx = (dy / tan(player->ray[i].angle));
		if (player->ray[i].angle > (PI / 2)
			&& player->ray[i].angle < (3 * PI / 2))
			x = (size_t)((player->location[0] - fabs(dx)) / (float)BLOCKSIZE);
		else
			x = (size_t)((player->location[0] + fabs(dx)) / (float)BLOCKSIZE);
		if (x >= ft_strlen(map[y]))
			break ;
		if (map[y][x] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		y++;
	}
	return (FLT_MAX);
}

float	collision_up(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	y = (size_t)(player->location[1] / (float)BLOCKSIZE);
	while (y > 0)
	{
		dy = (player->location[1] - y * BLOCKSIZE);
		dx = (dy / tan(player->ray[i].angle));
		if (player->ray[i].angle > (PI / 2)
			&& player->ray[i].angle < (3 * PI / 2))
			x = (size_t)((player->location[0] - fabs(dx)) / (float)BLOCKSIZE);
		else
			x = (size_t)((player->location[0] + fabs(dx)) / (float)BLOCKSIZE);
		if (x >= ft_strlen(map[y]))
			break ;
		if (map[y -1][x] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		y--;
	}
	return (FLT_MAX);
}

void	determine_wall(t_player *player, size_t i, float x, float y)
{
	if (x < y)
	{
		if (player->ray[i].angle > (PI / 2)
			&& player->ray[i].angle < (3 * PI / 2))
			player->ray[i].wall = WEST;
		else
			player->ray[i].wall = EAST;
	}
	else
	{
		if (player->ray[i].angle < PI)
			player->ray[i].wall = SOUTH;
		else
			player->ray[i].wall = NORTH;
	}
}

float	ray_len(t_player *player, size_t i, char **map)
{
	float	x;
	float	y;

	if (player->ray[i].angle == (PI / 2)
		|| player->ray[i].angle == (3 * PI / 2))
		x = FLT_MAX;
	else if (player->ray[i].angle > (PI / 2)
		&& player->ray[i].angle < (3 * PI / 2))
		x = collision_left(player, i, map);
	else
		x = collision_right(player, i, map);
	if (player->ray[i].angle == 0
		|| player->ray[i].angle == PI)
		y = FLT_MAX;
	else if (player->ray[i].angle < PI)
		y = collision_down(player, i, map);
	else
		y = collision_up(player, i, map);
	determine_wall(player, i, x, y);
	if (x < y)
		return (x);
	else
		return (y);
}
