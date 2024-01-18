/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window3d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:02:19 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/18 17:10:07 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	fps(void *param)
{
	char		*fps;
	t_cub3d		*cub3d;
	static int	f;

	cub3d = (t_cub3d *)param;
	if ((int)mlx_get_time() > 0)
	{
		fps = ft_itoa((f / (int)mlx_get_time()));
		printf("fps:\t%s\n", fps);
		mlx_put_string(cub3d->mlx, fps, 2, 2);
		free(fps);
	}
	f++;
}

void	init_window(t_cub3d *cub3d)
{
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	mlx_image_to_window(cub3d->mlx, cub3d->screen, 0, 0);
	redisplay(cub3d);
	mlx_key_hook(cub3d->mlx, &move_player, (void *)cub3d);
	mlx_loop_hook(cub3d->mlx, &fps, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
