/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:04:24 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 14:44:31 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "flags.h"

static bool	_init_textures(t_wall *walls, char *str, t_direction flag)
{
	mlx_texture_t	*image;

	if (!str)
		return (false);
	image = mlx_load_png(str);
	if (!image)
		return (false);
	printf("Texture: %s\n", str);
	if (image->width != image->height)
		return (mlx_delete_texture(image), false);
	walls->direction[flag] = image;
	return (true);
}

static t_color	*_init_color(char *str)
{
	t_color	*color;
	char	**color_values;

	if (!str)
		return (NULL);
	color_values = ft_split(ft_trim_whitespace(str), ',');
	if (!color_values)
		return (NULL);
	if (ft_arrlen(color_values) != 3)
		return (ft_free(color_values), NULL);
	if (!ft_isnumber(color_values[0])
		|| !ft_isnumber(color_values[1])
		|| !ft_isnumber(color_values[2]))
		return (NULL);
	color = ft_newcolor(ft_atoi(color_values[0]),
			ft_atoi(color_values[1]),
			ft_atoi(color_values[2]), 0xFF);
	return (ft_free(color_values), color);
}

static bool	initialize_map(t_map *map, char **flags)
{
	if (!map->walls)
		return (false);
	if (!_init_textures(map->walls, find_flag(flags, NORTH_FLAG), NORTH))
		return (false);
	if (!_init_textures(map->walls, find_flag(flags, SOUTH_FLAG), SOUTH))
		return (false);
	if (!_init_textures(map->walls, find_flag(flags, WEST_FLAG), WEST))
		return (false);
	if (!_init_textures(map->walls, find_flag(flags, EAST_FLAG), EAST))
		return (false);
	map->floor = _init_color(find_flag(flags, FLOOR_FLAG));
	if (!map->floor)
		return (false);
	map->ceiling = _init_color(find_flag(flags, CEILING_FLAG));
	if (!map->ceiling)
		return (false);
	return (true);
}

t_map	*read_map_from_file(char *filename)
{
	char	**map;
	t_map	*data;

	map = import_map(filename);
	if (!map)
		return (NULL);
	data = ft_calloc(1, sizeof(t_map));
	if (!data)
		return (ft_free(map), NULL);
	data->walls = ft_calloc(1, sizeof(t_wall));
	if (!initialize_map(data, map))
		return (ft_free(map), free_map(data), NULL);
	data->map = ft_arrdup(&map[6]);
	if (!data->map)
		return (ft_free(map), free_map(data), NULL);
	return (ft_arrfree(map), data);
}
