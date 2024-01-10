/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window3d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/25 20:11:23 by koen          #+#    #+#                 */
/*   Updated: 2024/01/10 18:24:47 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


//make sure to apply texture correclty depending on whether wall is higher than
//screen size or inside the drawing plane
void	test_draw_slices(mlx_t *mlx, t_player *player)
{
	mlx_image_t	*img[RAYS];

	for (size_t r = 0; r < RAYS; r++)
	{
		img[r] = mlx_new_image(mlx, (uint32_t)(WIDTH / RAYS),
				(uint32_t)roundf(player->ray[r].wall_height));
		int	val[3] = {250, 250 / (player->ray[r].corr_len / 100),
			250 / (player->ray[r].corr_len / 100)};
		set_color(img[r], val, WIDTH / RAYS
			* (size_t)player->ray[r].wall_height * sizeof(int32_t));
		mlx_image_to_window(mlx, img[r],
			(r * (WIDTH / RAYS)), HEIGHT / 2 - player->ray[r].wall_height / 2);
	}
	for (size_t r = 0; r < RAYS; r++)
	{
		mlx_delete_image(mlx, player->ray[r].slice);
		player->ray[r].slice = img[r];
	}
}

void	set_color2(mlx_image_t *image, int *value, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		image->pixels[i] = value[0];
		i += sizeof(int8_t);
		image->pixels[i] = value[1];
		i += sizeof(int8_t);
		image->pixels[i] = value[2];
		i += sizeof(int8_t);
		image->pixels[i] = 120;
		i += sizeof(int8_t);
	}
}

void	test(t_cub3d *cub3d)
{
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	test_draw_slices(cub3d->mlx, cub3d->player);
	mlx_key_hook(cub3d->mlx, &move_player, (void *)cub3d);
	mlx_loop_hook(cub3d->mlx, &redisplay, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
