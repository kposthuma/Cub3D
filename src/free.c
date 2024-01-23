/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 10:41:41 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 12:13:40 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void _cub3d_delete_texture(mlx_texture_t	*texture)
{
	if (texture)
	{
		free(texture->pixels);
		free(texture);
	}
}

void	free_map(t_map	*map)
{
	_cub3d_delete_texture(map->walls->north);
	_cub3d_delete_texture(map->walls->south);
	_cub3d_delete_texture(map->walls->west);
	_cub3d_delete_texture(map->walls->east);
	if (map->walls)
		free(map->walls);
	if (map->floor)
		free(map->floor);
	if (map->ceiling)
		free(map->ceiling);
	if (map->map)
	{
		ft_free((char **)map->map->cont);
		free(map->map);
	}
	if (map)
		free(map);
}

void	free_player(t_player *player)
{
	if (player)
	{
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
