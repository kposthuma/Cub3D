/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/01 14:07:57 by koen          #+#    #+#                 */
/*   Updated: 2024/01/03 18:18:33 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	collision_left(t_player *player, size_t i, char **map)
{
	size_t	x;
	size_t	y;
	float	dx;
	float	dy;
	float	theta;

	x = (size_t)(player->location[0] / (float)BLOCKSIZE);
	theta = calc_angle(player->ray[i].angle);
	while (x > 0)
	{
		dx = (player->location[0] - x * BLOCKSIZE);
		if (player->ray[i].angle > (3 * PI / 2))
		{
			dy = (dx * tan(theta));
			y = (size_t)((player->location[1] - dy) / (float)BLOCKSIZE);
		}
		else
		{
			dy = (dx / tan(theta));
			y = (size_t)((player->location[1] + dy) / (float)BLOCKSIZE);
		}
		if (y >= strofstrlen(map))
			break ;
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
	float	theta;

	x = (size_t)(player->location[0] / (float)BLOCKSIZE) + 1;
	theta = calc_angle(player->ray[i].angle);
	while (x < ft_strlen(map[0]))
	{
		dx = (player->location[0] - x * BLOCKSIZE);
		if (player->ray[i].angle < (PI / 2))
		{
			dy = (dx * tan(theta));
			y = (size_t)((player->location[1] - dy) / (float)BLOCKSIZE);
		}
		else
		{
			dy = (dx / tan(theta));
			y = (size_t)((player->location[1] + dy) / (float)BLOCKSIZE);
		}
		if (y >= strofstrlen(map))
			break ;
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
	float	theta;

	y = (size_t)(player->location[1] / (float)BLOCKSIZE) + 1;
	theta = calc_angle(player->ray[i].angle);
	while (y < strofstrlen(map))
	{
		dy = (player->location[1] - y * BLOCKSIZE);
		if (player->ray[i].angle > PI)
		{
			dx = (dy * tan(theta));
			x = (size_t)((player->location[0] - dx) / (float)BLOCKSIZE);
		}
		else
		{
			dx = (dy / tan(theta));
			x = (size_t)((player->location[0] + dx) / (float)BLOCKSIZE);
		}
		if (x >= ft_strlen(map[y]))
			break ;
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
	float	theta;

	y = (size_t)(player->location[1] / (float)BLOCKSIZE);
	theta = calc_angle(player->ray[i].angle);
	while (y > 0)
	{
		dy = (player->location[1] - y * BLOCKSIZE);
		if (player->ray[i].angle > PI)
		{
			dx = (dy / tan(theta));
			x = (size_t)((player->location[0] - dx) / (float)BLOCKSIZE);
		}
		else
		{
			dx = (dy * tan(theta));
			x = (size_t)((player->location[0] + dx) / (float)BLOCKSIZE);
		}
		if (x >= ft_strlen(map[y]))
			break ;
		if (map[y -1][x] == '1')
			return (sqrt(pow(dx, 2) + pow(dy, 2)));
		y--;
	}
	return (WIDTH);
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
		y = WIDTH;
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
