/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:05:36 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 12:38:15 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
