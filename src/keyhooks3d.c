/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyhooks3d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/29 18:42:05 by koen          #+#    #+#                 */
/*   Updated: 2024/01/11 13:30:22 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	determine_xy(t_player *player, bool hor)
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

void	walk_player(t_cub3d *cub3d, bool forward)
{
	char	**map;
	float	tempx;
	float	tempy;

	determine_xy(cub3d->player, true);
	map = (char **)((find_node(cub3d->data, MAP_START))->cont);
	if (!forward)
	{
		cub3d->player->dx *= -1;
		cub3d->player->dy *= -1;
	}
	tempx = cub3d->player->location[0] + cub3d->player->dx;
	if (map[(size_t)cub3d->player->location[1] / BLOCKSIZE]
		[(size_t)(tempx) / BLOCKSIZE]
		== '1')
		cub3d->player->dx = 0;
	cub3d->player->location[0] += cub3d->player->dx;
	tempy = cub3d->player->location[1] + cub3d->player->dy;
	if (map
		[(size_t)(tempy) / BLOCKSIZE]
		[(size_t)cub3d->player->location[0] / BLOCKSIZE] == '1')
		cub3d->player->dy = 0;
	cub3d->player->location[1] += cub3d->player->dy;
	cub3d->moved = true;
}

void	strafe_player(t_cub3d *cub3d, bool left)
{
	char	**map;
	float	tempx;
	float	tempy;

	determine_xy(cub3d->player, false);
	map = (char **)((find_node(cub3d->data, MAP_START))->cont);
	if (!left)
	{
		cub3d->player->dx *= -1;
		cub3d->player->dy *= -1;
	}
	tempx = cub3d->player->location[0] + cub3d->player->dx;
	if (map[(size_t)cub3d->player->location[1] / BLOCKSIZE]
		[(size_t)(tempx) / BLOCKSIZE]
		== '1')
		cub3d->player->dx = 0;
	cub3d->player->location[0] += cub3d->player->dx;
	tempy = cub3d->player->location[1] + cub3d->player->dy;
	if (map
		[(size_t)(tempy) / BLOCKSIZE]
		[(size_t)cub3d->player->location[0] / BLOCKSIZE] == '1')
		cub3d->player->dy = 0;
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
		&& keydata.key == MLX_KEY_W)
		walk_player(cub3d, true);
	else if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_S)
		walk_player(cub3d, false);
	if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_A)
		strafe_player(cub3d, true);
	else if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_D)
		strafe_player(cub3d, false);
	if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_LEFT)
		turn_player(cub3d, true);
	else if ((keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		&& keydata.key == MLX_KEY_RIGHT)
		turn_player(cub3d, false);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cub3d->mlx);
}
