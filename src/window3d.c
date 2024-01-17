/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window3d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:02:19 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/17 11:02:29 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_window(t_cub3d *cub3d)
{
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	mlx_image_to_window(cub3d->mlx, cub3d->screen, 0, 0);
	redisplay(cub3d);
	mlx_key_hook(cub3d->mlx, &move_player, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
