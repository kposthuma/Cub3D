#include "cub3d.h"

static bool _init_data_textures(t_data **data, char *str, t_flag flag)
{
	t_img_data	*image;
	t_data		*new;
	
	image = ft_calloc(1, sizeof(t_img_data));
	if (!image)
		return (false);
	image->texture = mlx_load_png(str);
	if (!image->texture)
		return (false);
	new = newnode(image);
	new->flag = flag;
	add_node(data, new);
	printf("Successfully loaded %s\n", str);
	return (true);
}

static bool	_init_data_struct(t_data **data, char **map)
{
	t_data	*tmp;
	size_t	index;
	
	index = 0;
	tmp = newnode(&map[index]);
	if (!tmp)
		return (false);
	tmp->flag = MAP_START;
	add_node(data, tmp);
	return (true);
}

t_data	*read_map_from_file(char *filename)
{
	char	**map;
	t_data	*head;
	t_data	*tmp;

	head = NULL;
	map = import_map(filename);
	if (!map)
		return (NULL);
	for (int i = 0; map[i]; i++)
		printf("Map: %s\n", map[i]);
	if (!_init_data_textures(&head, find_flag(map, "NO"), N_TEXTURE))
		return (NULL);
	if (!_init_data_textures(&head, find_flag(map, "SO"), S_TEXTURE))
		return (NULL);
	if (!_init_data_textures(&head, find_flag(map, "WE"), W_TEXTURE))
		return (NULL);
	if (!_init_data_textures(&head, find_flag(map, "EA"), E_TEXTURE))
		return (NULL);

	/* more dumb shit */
	int c1[3] = { 120, 120, 120 };
	tmp = newnode((void *)c1);
	tmp->flag = C_COLOR;
	add_node(&head, tmp);

	int c2[3] = { 120, 120, 120 };
	tmp = newnode((void *)c2);
	tmp->flag = F_COLOR;
	add_node(&head, tmp);

	if (!_init_data_struct(&head, &map[6]))
		return (NULL);
	return (head);
}
