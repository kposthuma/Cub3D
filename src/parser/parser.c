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

static bool	_init_textures(t_data **data, char *str, t_flag flag)
{
	mlx_texture_t	*image;
	t_data			*new;

	image = mlx_load_png(str);
	if (!image)
		return (false);
	if (image->width != IMAGE_SIZE
		&& image->width != IMAGE_SIZE
		&& image->width != image->height)
	{
		mlx_delete_texture(image);
		return (false);
	}
	if (!_add_node(data, image, flag))
		return (false);
	printf("Successfully loaded %s\n", str);
	return (true);
}

static t_map	*_create_map(t_data *textures, t_data *cont)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->flags = textures;
	map->map = cont;
	map->size = strofstrlen((char **)map->map->cont);
	return (map);
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
	if (!_init_textures(&textures, find_flag(map, NORTH_FLAG), N_TEXTURE))
		return (NULL);
	if (!_init_textures(&textures, find_flag(map, SOUTH_FLAG), S_TEXTURE))
		return (NULL);
	if (!_init_textures(&textures, find_flag(map, WEST_FLAG), W_TEXTURE))
		return (NULL);
	if (!_init_textures(&textures, find_flag(map, EAST_FLAG), E_TEXTURE))
		return (NULL);
	if (!_add_node(&textures, (void *)color, C_COLOR))
		return (NULL);
	if (!_add_node(&textures, (void *) color, F_COLOR))
		return (NULL);
	if (!_add_node(&map_struct, &map[6], MAP_START))
		return (NULL);
	data = _create_map(textures, map_struct);
	if (!data)
		return (NULL);
	return (data);
}
