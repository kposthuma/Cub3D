/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks3d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 18:42:05 by koen          #+#    #+#                 */
/*   Updated: 2023/12/30 20:15:51 by koen          ########   odam.nl         */
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

void	determine_xy(float theta, t_player *player)
{
	float	temp;

	player->dx = STEPSIZE * sin(theta);
	if (player->angle > PI)
		player->dx *= -1;
	player->dy = STEPSIZE * cos(theta);
	if (player->angle < PI / 2 || player->angle > (3 * PI / 2))
		player->dy *= -1;
	if (player->dx * player->dy > 0)
	{
		temp = player->dx;
		player->dx = player->dy;
		player->dy = temp;
	}
}

void	walk_player(t_cub3d *cub3d, bool forward)
{
	float	theta;

	theta = calc_angle(cub3d->player->angle);
	determine_xy(theta, cub3d->player);
	if (!forward)
	{
		cub3d->player->dx *= -1;
		cub3d->player->dy *= -1;
	}
	cub3d->player->location[0] += cub3d->player->dx;
	cub3d->player->location[1] += cub3d->player->dy;
	// check for walls
}

void	turn_player(t_cub3d *cub3d, bool left)
{
	if (!left)
		cub3d->player->angle += (PI / 6);
	else
		cub3d->player->angle -= (PI / 6);
	if (cub3d->player->angle >= (2 * PI))
		cub3d->player->angle -= (2 * PI);
	else if (cub3d->player->angle < 0)
		cub3d->player->angle += (2 * PI);
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
}
