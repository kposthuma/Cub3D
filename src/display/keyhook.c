/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhook.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:07:56 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 17:18:50 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	determine_xy(t_player *player, bool hor)
{
	if (hor)
	{
		player->dx = STEPSIZE * cos(player->angle);
		player->dy = STEPSIZE * sin(player->angle);
	}
	else
	{
		player->dx = STEPSIZE * sin(player->angle);
		player->dy = STEPSIZE * -cos(player->angle);
	}
}

static void	turn_around(t_cub3d *cub3d)
{
	cub3d->player->dx *= -1;
	cub3d->player->dy *= -1;
}

static void	walk_player(t_cub3d *cub3d, bool forward, bool hor)
{
	char	**map;
	float	tempx;
	float	tempy;

	determine_xy(cub3d->player, hor);
	map = (char **) cub3d->map->map;
	if (!forward)
		turn_around(cub3d);
	tempx = cub3d->player->location[0] + cub3d->player->dx;
	tempy = cub3d->player->location[1] + cub3d->player->dy;
	if (player_collision_x(cub3d, map, tempx))
		cub3d->player->dx = 0;
	if (player_collision_y(cub3d, map, tempy))
		cub3d->player->dy = 0;
	cub3d->player->location[0] += cub3d->player->dx;
	cub3d->player->location[1] += cub3d->player->dy;
}

void	turn_player(t_cub3d *cub3d, bool left)
{
	if (!left)
		cub3d->player->angle += (PI / 48);
	else
		cub3d->player->angle -= (PI / 48);
	if (cub3d->player->angle >= (2 * PI))
		cub3d->player->angle -= (2 * PI);
	else if (cub3d->player->angle < 0)
		cub3d->player->angle += (2 * PI);
}

void	move_player(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_W))
		walk_player(cub3d, true, true);
	else if (mlx_is_key_down(cub3d->mlx, MLX_KEY_S))
		walk_player(cub3d, false, true);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_A))
		walk_player(cub3d, true, false);
	else if (mlx_is_key_down(cub3d->mlx, MLX_KEY_D))
		walk_player(cub3d, false, false);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_LEFT))
		turn_player(cub3d, true);
	else if (mlx_is_key_down(cub3d->mlx, MLX_KEY_RIGHT))
		turn_player(cub3d, false);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub3d->mlx);
}
