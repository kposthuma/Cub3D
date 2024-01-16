#include "cub3d.h"
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

static bool	_init_data_textures(t_data **data, char *str, t_flag flag)
{
	t_img_data	*image;
	t_data		*new;

	image = ft_calloc(1, sizeof(t_img_data));
	if (!image)
		return (false);
	image->texture = mlx_load_png(str);
	if (!image->texture)
		return (false);
	if (image->texture->width != image->texture->height)
	{
		mlx_delete_texture(image->texture);
		return (false);
	}
	if (!_add_node(data, image, flag))
		return (false);
	printf("Successfully loaded %s\n", str);
	return (true);
}

t_map	*read_map_from_file(char *filename)
{
	const int	color[3] = {120, 120, 120};
	char		**map;
	t_data		*textures;
	t_data		*map_struct;
	t_map		*data;

	data = NULL;
	textures = NULL;
	map_struct = NULL;
	map = import_map(filename);
	if (!map)
		return (NULL);
	if (!_init_data_textures(&textures, find_flag(map, NORTH_TEXTURE_FLAG), N_TEXTURE))
		return (NULL);
	if (!_init_data_textures(&textures, find_flag(map, SOUTH_TEXTURE_FLAG), S_TEXTURE))
		return (NULL);
	if (!_init_data_textures(&textures, find_flag(map, WEST_TEXTURE_FLAG), W_TEXTURE))
		return (NULL);
	if (!_init_data_textures(&textures, find_flag(map, EAST_TEXTURE_FLAG), E_TEXTURE))
		return (NULL);
	if (!_add_node(&textures, (void *)color, C_COLOR))
		return (NULL);
	if (!_add_node(&textures, (void *) color, F_COLOR))
		return (NULL);
	if (!_add_node(&map_struct, &map[6], MAP_START))
		return (NULL);
	data = ft_calloc(1, sizeof(t_map));
	if (!data)
		return (NULL);
	data->flags = textures;
	data->map = map_struct;
	data->size = 1000;
	return (data);
}
