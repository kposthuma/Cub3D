/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks3d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 18:42:05 by koen          #+#    #+#                 */
/*   Updated: 2024/01/10 14:09:17 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

float	calc_angle(float angle)
{
	if (angle < (PI / 2))
		return (angle);
	if (angle < PI)
		return (angle - (PI / 2));
	if (angle < (3 * PI / 2))
		return (angle - PI);
	else
		return (angle - (3 * PI / 2));
}

void	determine_xy(t_player *player)
{
	player->dx = STEPSIZE * cos(player->angle);
	player->dy = STEPSIZE * sin(player->angle);
}

	// check for walls
void	walk_player(t_cub3d *cub3d, bool forward)
{
	determine_xy(cub3d->player);
	if (!forward)
	{
		cub3d->player->dx *= -1;
		cub3d->player->dy *= -1;
	}
	cub3d->player->location[0] += cub3d->player->dx;
	cub3d->player->location[1] += cub3d->player->dy;
	cub3d->moved = true;
}

void	turn_player(t_cub3d *cub3d, bool left)
{
	if (!left)
		cub3d->player->angle += (PI / 12);
	else
		cub3d->player->angle -= (PI / 12);
	if (cub3d->player->angle >= (2 * PI))
		cub3d->player->angle -= (2 * PI);
	else if (cub3d->player->angle < 0)
		cub3d->player->angle += (2 * PI);
	cub3d->moved = true;
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_UP)
		walk_player(cub3d, true);
	else if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_DOWN)
		walk_player(cub3d, false);
	if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_LEFT)
		turn_player(cub3d, true);
	else if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_RIGHT)
		turn_player(cub3d, false);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cub3d->mlx);
}
