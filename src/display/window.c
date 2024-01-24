/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:02:19 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/24 14:14:51 by kposthum      ########   odam.nl         */
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

void	mouse(void *param)
{
	t_cub3d			*cub3d;
	static int32_t	x;
	static int32_t	y;
	static bool		enable = true;

	cub3d = (t_cub3d *)param;
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_Q))
		enable = !enable;
	if (enable)
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

static void	fps(void *param)
{
	static mlx_image_t	*fps_counter = NULL;
	mlx_t				*mlx;
	static double		old;
	double				new;
	char				*text;

	mlx = ((t_cub3d *)param)->mlx;
	new = mlx_get_time();
	if (new > 0)
	{
		text = ft_itoa((int)1.0 / (new - old));
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
	mlx_loop_hook(cub3d->mlx, &mouse, (void *)cub3d);
	mlx_resize_hook(cub3d->mlx, &resize, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
