/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:02:19 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 15:07:54 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize(int32_t width, int32_t height, void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	cub3d->floor->instances->y = height / 2;
	cub3d->player->raycount = width;
	free(cub3d->player->ray);
	cub3d->player->ray = ft_calloc(width, sizeof(t_ray));
	if (!mlx_resize_image(cub3d->screen, width, height)
		|| !mlx_resize_image(cub3d->ceiling, width, height / 2)
		|| !mlx_resize_image(cub3d->floor, width, height / 2)
		|| !cub3d->player->ray)
		mlx_close_window(cub3d->mlx);
	else
		redisplay(cub3d);
}

static void	fps(void *param)
{
	static mlx_image_t	*fps_counter = NULL;
	mlx_t				*mlx;
	static double		old;
	double				new;
	char				*text;

	mlx = ((t_cub3d *)param)->mlx;
	new = mlx_get_time();
	mlx_delete_image(mlx, fps_counter);
	if (new > 0 && ((t_cub3d *)param)->fps == true)
	{
		text = ft_itoa((int)1.0 / (new - old));
		if (text)
			fps_counter = mlx_put_string((mlx_t *)mlx, text, 10, 10);
		if (!text || (text && !fps_counter))
		{
			mlx_delete_image(mlx, fps_counter);
			free(text);
			mlx_close_window(mlx);
		}
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
		angle = player->angle;
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
	mlx_loop_hook(cub3d->mlx, &mouse, (void *)cub3d);
	mlx_resize_hook(cub3d->mlx, &resize, (void *)cub3d);
	mlx_key_hook(cub3d->mlx, &toggle, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
