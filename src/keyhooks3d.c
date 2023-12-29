/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks3d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 18:42:05 by koen          #+#    #+#                 */
/*   Updated: 2023/12/29 19:40:21 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

float	determine_x(float theta, float angle)
{
	float	dx;

	dx = STEPSIZE * sin(theta);
	if (angle > PI)
		dx *= -1;
	return (dx);
}

float	determine_y(float theta, float angle)
{
	float	dy;

	dy = STEPSIZE * cos(theta);
	if (angle < PI / 2 || angle > (3 * PI / 2))
		dy *= -1;
	return (dy);
}

void	walk_player(t_cub3d *cub3d, bool forward)
{
	float	theta;
	float	dx;
	float	dy;

	theta = calc_angle(cub3d->player->angle);
	dx = determine_x(theta, cub3d->player->angle);
	dy = determine_y(theta, cub3d->player->angle);
	if (!forward)
	{
		cub3d->player->location[0] += dx;
		cub3d->player->location[1] += dy;
	}
	else
	{
		cub3d->player->location[0] -= dx;
		cub3d->player->location[1] -= dy;
	}
	// maybe check for walls?
}

void	turn_player(t_cub3d *cub3d, bool left)
{
	if (!left)
		cub3d->player->angle++;
	else
		cub3d->player->angle--;
	if (cub3d->player->angle >= (2 * PI))
		cub3d->player->angle -= (2 * PI);
	else if (cub3d->player->angle < 0)
		cub3d->player->angle += (2 * PI);
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) && keydata.key == MLX_KEY_UP)
		walk_player(cub3d, false);
	else if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) && keydata.key == MLX_KEY_DOWN)
		walk_player(cub3d, false);
	if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) && keydata.key == MLX_KEY_LEFT)
		turn_player(cub3d, true);
	else if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) && keydata.key == MLX_KEY_RIGHT)
		turn_player(cub3d, false);
}
