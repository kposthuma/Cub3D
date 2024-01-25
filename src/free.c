/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 10:41:41 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 13:10:07 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map	*map)
{
	mlx_delete_texture(map->walls->north);
	mlx_delete_texture(map->walls->south);
	mlx_delete_texture(map->walls->west);
	mlx_delete_texture(map->walls->east);
	if (map->walls)
		free(map->walls);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
	if (map->map)
		ft_arrfree(map->map);
	if (map)
		free(map);
}

void	free_player(t_player *player)
{
	if (player)
	{
		free(player->ray);
		free(player);
	}
}

void	free_cub3d(t_cub3d *cub)
{
	if (cub->map)
		free_map(cub->map);
	if (cub->ceiling && cub->mlx)
		mlx_delete_image(cub->mlx, cub->ceiling);
	if (cub->floor && cub->mlx)
		mlx_delete_image(cub->mlx, cub->floor);
	if (cub->screen && cub->mlx)
		mlx_delete_image(cub->mlx, cub->screen);
	if (cub->player)
		free_player(cub->player);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}
