/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 10:43:29 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 13:50:21 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	collision_left(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;

	x = (size_t)(player->location[0] / (float)BLOCK);
	while (x > 0)
	{
		dx = (player->location[0] - x * BLOCK);
		dy = (dx * tan(player->ray[i].angle));
		if (player->ray[i].angle > PI)
			y = (size_t)((player->location[1] - fabs(dy)) / (float)BLOCK);
		else
			y = (size_t)((player->location[1] + fabs(dy)) / (float)BLOCK);
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
	size_t			x;
	size_t			y;
	float			dx;
	float			dy;

	x = (size_t)(player->location[0] / (float)BLOCK) + 1;
	y = (size_t)((player->location[1]) / (float)BLOCK);
	while (x < ft_strlen(map[y]))
	{
		dx = (player->location[0] - x * BLOCK);
		dy = (dx * tan(player->ray[i].angle));
		if (player->ray[i].angle > PI)
			y = (size_t)((player->location[1] - fabs(dy)) / (float)BLOCK);
		else
			y = (size_t)((player->location[1] + fabs(dy)) / (float)BLOCK);
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
	const size_t	len = ft_arrlen(map);
	size_t			x;
	size_t			y;
	float			dx;
	float			dy;

	y = (size_t)(player->location[1] / (float)BLOCK) + 1;
	while (y < len)
	{
		dy = (player->location[1] - y * BLOCK);
		dx = (dy / tan(player->ray[i].angle));
		if (player->ray[i].angle > (PI / 2)
			&& player->ray[i].angle < (3 * PI / 2))
			x = (size_t)((player->location[0] - fabs(dx)) / (float)BLOCK);
		else
			x = (size_t)((player->location[0] + fabs(dx)) / (float)BLOCK);
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

	y = (size_t)(player->location[1] / (float)BLOCK);
	while (y > 0)
	{
		dy = (player->location[1] - y * BLOCK);
		dx = (dy / tan(player->ray[i].angle));
		if (player->ray[i].angle > (PI / 2)
			&& player->ray[i].angle < (3 * PI / 2))
			x = (size_t)((player->location[0] - fabs(dx)) / (float)BLOCK);
		else
			x = (size_t)((player->location[0] + fabs(dx)) / (float)BLOCK);
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
