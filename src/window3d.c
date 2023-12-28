/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window3d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/25 20:11:23 by koen          #+#    #+#                 */
/*   Updated: 2023/12/28 15:09:12 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

void test(t_cub3d *cub3d)
{
	mlx_image_t *player = mlx_new_image(cub3d->mlx, cub3d->mlx->width / 160, cub3d->mlx->height / 90);
	int val[3] = {50, 50, 255};

	set_color(player, val, (cub3d->mlx->width / 160) * (cub3d->mlx->height / 90) * sizeof(int32_t));
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	mlx_image_to_window(cub3d->mlx, player, (cub3d->player->start.x * 100) + 45,
		(cub3d->player->start.y * 100) + 45);
	
	mlx_loop(cub3d->mlx);
}