/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 14:24:35 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 17:17:36 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	toggle(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
	{
		mlx_set_mouse_pos(((t_cub3d *)param)->mlx,
			((t_cub3d *)param)->mlx->width / 2,
			((t_cub3d *)param)->mlx->height / 2);
		((t_cub3d *)param)->mouse = !((t_cub3d *)param)->mouse;
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS)
		((t_cub3d *)param)->fps = !((t_cub3d *)param)->fps;
}

bool	player_collision_x(t_cub3d *cub3d, char **map, float tempx)
{
	if ((cub3d->player->dx > 0 && map[(size_t)(cub3d->player->location[1]
				- cub3d->player->plane) / BLOCK]
		[(size_t)(tempx + cub3d->player->plane) / BLOCK] == '1'))
		return (true);
	if ((cub3d->player->dx > 0 && map[(size_t)(cub3d->player->location[1]
				+ cub3d->player->plane) / BLOCK]
		[(size_t)(tempx + cub3d->player->plane) / BLOCK] == '1'))
		return (true);
	if ((cub3d->player->dx < 0 && map[(size_t)(cub3d->player->location[1]
				- cub3d->player->plane) / BLOCK]
		[(size_t)(tempx - cub3d->player->plane) / BLOCK] == '1'))
		return (true);
	if ((cub3d->player->dx < 0 && map[(size_t)(cub3d->player->location[1]
				+ cub3d->player->plane) / BLOCK]
		[(size_t)(tempx - cub3d->player->plane) / BLOCK] == '1'))
		return (true);
	return (false);
}

bool	player_collision_y(t_cub3d *cub3d, char **map, float tempy)
{
	if ((cub3d->player->dy < 0 && map[(size_t)(tempy - cub3d->player->plane)
			/ BLOCK][(size_t)(cub3d->player->location[0] + cub3d->player->plane)
		/ BLOCK] == '1'))
		return (true);
	if ((cub3d->player->dy < 0 && map[(size_t)(tempy - cub3d->player->plane)
			/ BLOCK][(size_t)(cub3d->player->location[0] - cub3d->player->plane)
		/ BLOCK] == '1'))
		return (true);
	if ((cub3d->player->dy > 0 && map[(size_t)(tempy + cub3d->player->plane)
			/ BLOCK][(size_t)(cub3d->player->location[0] + cub3d->player->plane)
		/ BLOCK] == '1'))
		return (true);
	if ((cub3d->player->dy > 0 && map[(size_t)(tempy + cub3d->player->plane)
			/ BLOCK][(size_t)(cub3d->player->location[0] - cub3d->player->plane)
		/ BLOCK] == '1'))
		return (true);
	return (false);
}
