/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 10:43:29 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 10:43:31 by kposthum      ########   odam.nl         */
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
	const size_t	len = ft_strlen(map[(int)player->location[1] / BLOCKSIZE]);
	size_t			x;
	size_t			y;
	float			dx;
	float			dy;

	x = (size_t)(player->location[0] / (float)BLOCKSIZE) + 1;
	while (x < len)
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
	const size_t	len = ft_arrlen(map);
	size_t			x;
	size_t			y;
	float			dx;
	float			dy;

	y = (size_t)(player->location[1] / (float)BLOCKSIZE) + 1;
	while (y < len)
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
