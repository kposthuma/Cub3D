/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window3d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/25 20:11:23 by koen          #+#    #+#                 */
/*   Updated: 2023/12/31 15:53:28 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	test_draw_map(mlx_t *mlx, mlx_image_t *wall,
	mlx_image_t *tile, t_data **data)
{
	t_data	*node = find_node(data, MAP_START);
	char	**map = (char **)node->cont;

	for (size_t y = 0; map[y]; y++)
	{
		for (size_t x = 0; map[y][x]; x++)
		{
			if (map[y][x] == '1')
				mlx_image_to_window(mlx, wall, (x * BLOCKSIZE) + 1, (y * BLOCKSIZE) + 1);
			else
				mlx_image_to_window(mlx, tile, (x * BLOCKSIZE) + 1, (y * BLOCKSIZE) + 1);
		}
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
	mlx_image_t	*player = mlx_new_image(cub3d->mlx, BLOCKSIZE / 10,
			BLOCKSIZE / 10);
	mlx_image_t	*wall = mlx_new_image(cub3d->mlx, (BLOCKSIZE) - 2,
			(BLOCKSIZE) - 2);
	mlx_image_t	*tile = mlx_new_image(cub3d->mlx, (BLOCKSIZE) - 2,
			(BLOCKSIZE) - 2);
	int			val[3] = {50, 50, 255};
	int			val2[3] = {0, 0, 0};
	int			val3[3] = {250, 250, 250};

	set_color(player, val,
		(BLOCKSIZE / 10) * (BLOCKSIZE / 10) * sizeof(int32_t));
	set_color2(wall, val2,
		(BLOCKSIZE - 2) * (BLOCKSIZE - 2) * sizeof(int32_t));
	set_color2(tile, val3,
		(BLOCKSIZE - 2)	* (BLOCKSIZE - 2) * sizeof(int32_t));
	cub3d->player->test = player;
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	test_draw_map(cub3d->mlx, wall, tile, cub3d->data);
	mlx_image_to_window(cub3d->mlx, player,
		(cub3d->player->start.x * BLOCKSIZE) + BLOCKSIZE / 2 - BLOCKSIZE / 20,
		(cub3d->player->start.y * BLOCKSIZE) + BLOCKSIZE / 2 - BLOCKSIZE / 20);
	mlx_key_hook(cub3d->mlx, &move_player, (void *)cub3d);
	mlx_loop_hook(cub3d->mlx, &redisplay, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
