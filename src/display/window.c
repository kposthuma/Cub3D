/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:02:19 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 14:21:59 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fps(void *param)
{
	static	mlx_image_t	*fps_counter = NULL;
	mlx_t				*mlx = ((t_cub3d *)param)->mlx;
	static double	old;
	double			new;
	int				num;
	char			*text;

	new = mlx_get_time();
	if (new > 0)
	{
		num = (int)1.0 / (new - old);
		text = ft_itoa(num);
		mlx_delete_image(mlx, fps_counter);
		if (text)
			fps_counter = mlx_put_string((mlx_t *)mlx, text, 10, 10);
		free(text);
	}
	old = new;
}

static void	game_loop(void *param)
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

void	init_window(t_cub3d *cub3d)
{
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	mlx_image_to_window(cub3d->mlx, cub3d->screen, 0, 0);
	mlx_loop_hook(cub3d->mlx, &game_loop, (void *)cub3d);
	mlx_loop_hook(cub3d->mlx, &move_player, (void *)cub3d);
	mlx_loop_hook(cub3d->mlx, &fps, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
