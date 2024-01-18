/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:04:24 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/18 15:21:58 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "color.h"
#include "flags.h"

static bool	_add_node(t_data **list, void *content, t_flag type)
{
	t_data	*tmp;

	tmp = newnode(content);
	if (!tmp)
		return (false);
	tmp->flag = type;
	add_node(list, tmp);
	return (true);
}

static bool	_init_textures(t_data **data, char *str, t_flag flag)
{
	mlx_texture_t	*image;
	t_data			*new;

	image = mlx_load_png(str);
	if (!image)
		return (false);
	if (image->width != image->height)
		return (mlx_delete_texture(image), false);
	if (!_add_node(data, image, flag))
		return (mlx_delete_texture(image), false);
	return (true);
}

static int	_get_color(const char *str)
{
	printf("Color: [%s]\n", str);
	return (ft_atoi(str));
}

static bool	_init_color(t_data **data, char *str, t_flag flag)
{
	char	**color_values;
	t_color	*color;

	color_values = ft_split(str, ',');
	if (!color_values)
		return (false);
	color = malloc(sizeof(t_color));
	if (!color)
		return (ft_free(color_values), false);
	color->r = _get_color(color_values[0]);
	color->g = _get_color(color_values[1]);
	color->b = _get_color(color_values[2]);
	color->a = 200;
	if (!_add_node(data, color, flag))
		return (ft_free(color_values), false);
	return (ft_free(color_values), true);
}

static t_map	*_create_map(t_data *textures, t_data *cont)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->flags = textures;
	map->map = cont;
	return (map);
}

t_map	*read_map_from_file(char *filename)
{
	char		**map;
	t_data		*textures;
	t_data		*map_struct;
	t_map		*data;

	textures = NULL;
	map_struct = NULL;
	map = import_map(filename);
	if (!map)
		return (NULL);
	_init_textures(&textures, find_flag(map, NORTH_FLAG), N_TEXTURE);
	_init_textures(&textures, find_flag(map, SOUTH_FLAG), S_TEXTURE);
	_init_textures(&textures, find_flag(map, WEST_FLAG), W_TEXTURE);
	_init_textures(&textures, find_flag(map, EAST_FLAG), E_TEXTURE);
	_init_color(&textures, find_flag(map, FLOOR_FLAG), F_COLOR);
	_init_color(&textures, find_flag(map, CEILING_FLAG), C_COLOR);
	_add_node(&map_struct, &map[6], MAP_START);
	data = _create_map(textures, map_struct);
	if (!data)
		return (NULL);
	return (data);
}
