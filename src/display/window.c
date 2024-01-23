/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:02:19 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 13:33:29 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fps(void *param)
{
	static double	old;
	double			new;

	(void)param;
	new = mlx_get_time();
	if (new > 0)
		printf("fps <%f>\n", 1.0 / (new - old));
	old = new;
}

void	game_loop(void *param)
{
	const t_cub3d	*cub = (t_cub3d *)param;
	const t_player	*player = cub->player;
	static float	x = -1;
	static float	y = -1;
	static float	angle = -1;

	if (x != player->dx || y != player->dy || angle != player->angle)
	{
		x = player->dx;
		y = player->dy;
	}
	redisplay((t_cub3d *)cub);
}

	// mlx_loop_hook(cub3d->mlx, &fps, (void *)cub3d);
void	init_window(t_cub3d *cub3d)
{
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	mlx_image_to_window(cub3d->mlx, cub3d->screen, 0, 0);
	mlx_loop_hook(cub3d->mlx, &game_loop, (void *)cub3d);
	mlx_loop_hook(cub3d->mlx, &move_player, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
