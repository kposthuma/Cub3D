/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 14:24:35 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/24 14:32:26 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	disable(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		((t_cub3d *)param)->mouse = !((t_cub3d *)param)->mouse;
}

void	mouse(void *param)
{
	t_cub3d			*cub3d;
	static int32_t	x;
	static int32_t	y;

	cub3d = (t_cub3d *)param;
	if (cub3d->mouse)
	{
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_HIDDEN);
		mlx_get_mouse_pos(cub3d->mlx, &x, &y);
		if (x < cub3d->mlx->width / 2)
			turn_player(cub3d, true);
		else if (x > cub3d->mlx->width / 2)
			turn_player(cub3d, false);
		mlx_set_mouse_pos(cub3d->mlx, cub3d->mlx->width / 2,
			cub3d->mlx->height / 2);
	}
	else
		mlx_set_cursor_mode(cub3d->mlx, MLX_MOUSE_NORMAL);
}
