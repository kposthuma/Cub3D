/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window3d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/25 20:11:23 by koen          #+#    #+#                 */
/*   Updated: 2024/01/10 15:42:05 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void	test_draw_map(mlx_t *mlx, mlx_image_t *wall,
// 	mlx_image_t *tile, t_data **data)
// {
// 	char	**map = (char **)(find_node(data, MAP_START)->cont);

// 	for (size_t y = 0; map[y]; y++)
// 	{
// 		for (size_t x = 0; map[y][x]; x++)
// 		{
// 			if (map[y][x] == '1')
// 				mlx_image_to_window(mlx, wall,
// 					(x * BLOCKSIZE) + 1, (y * BLOCKSIZE) + 1);
// 			else
// 				mlx_image_to_window(mlx, tile,
// 					(x * BLOCKSIZE) + 1, (y * BLOCKSIZE) + 1);
// 		}
// 	}
// }

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
	mlx_image_t	*wall = mlx_new_image(cub3d->mlx, (BLOCKSIZE) - 2,
			(BLOCKSIZE) - 2);
	mlx_image_t	*tile = mlx_new_image(cub3d->mlx, (BLOCKSIZE) - 2,
			(BLOCKSIZE) - 2);
	static int	val[3] = {50, 50, 255};
	static int	val1[3] = {50, 255, 255};
	static int	val2[3] = {0, 0, 0};
	static int	val3[3] = {250, 250, 250};

	cub3d->player->test = mlx_new_image(cub3d->mlx, BLOCKSIZE / 10,
			BLOCKSIZE / 10);
	cub3d->player->raydot = mlx_new_image(cub3d->mlx, 2, 2);
	set_color(cub3d->player->test, val,
		(BLOCKSIZE / 10) * (BLOCKSIZE / 10) * sizeof(int32_t));
	set_color(cub3d->player->raydot, val1,
		2 * 2 * sizeof(int32_t));
	set_color2(wall, val2,
		(BLOCKSIZE - 2) * (BLOCKSIZE - 2) * sizeof(int32_t));
	set_color2(tile, val3,
		(BLOCKSIZE - 2) * (BLOCKSIZE - 2) * sizeof(int32_t));
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	// test_draw_map(cub3d->mlx, wall, tile, cub3d->data);
	// mlx_image_to_window(cub3d->mlx, cub3d->player->test,
	// 	(cub3d->player->start.x * BLOCKSIZE) + BLOCKSIZE / 2 - BLOCKSIZE / 20,
	// 	(cub3d->player->start.y * BLOCKSIZE) + BLOCKSIZE / 2 - BLOCKSIZE / 20);
	// for (size_t r = 0; r < RAYS; r++)
	// {
	// 	mlx_image_to_window(cub3d->mlx, cub3d->player->raydot,
	// 		cub3d->player->ray[r].x, cub3d->player->ray[r].y);
	// }
	test_draw_slices(cub3d->mlx, cub3d->player);
	mlx_key_hook(cub3d->mlx, &move_player, (void *)cub3d);
	mlx_loop_hook(cub3d->mlx, &redisplay, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
