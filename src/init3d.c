/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 18:51:06 by koen          #+#    #+#                 */
/*   Updated: 2023/12/28 19:20:19 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	determine_angle(char **map, t_location loc)
{
	if (map[loc.y][loc.x] == 'N')
		return (PI / 2);
	if (map[loc.y][loc.x] == 'E')
		return (0);
	if (map[loc.y][loc.x] == 'S')
		return (PI + PI / 2);
	if (map[loc.y][loc.x] == 'W')
		return (PI);
	else
		return (-1);
}

t_player	*init_player(t_data **head)
{
	t_data		*node;
	char		**map;
	t_player	*player;

	node = find_node(head, MAP_START);
	map = (char **)node->cont;
	player = ft_calloc(1, sizeof(t_player));
	player->start = find_loc(map, "NESW");
	player->angle  = determine_angle(map, player->start);
	player->location[0] = player->start.x * BLOCKSIZE + BLOCKSIZE / 2;
	player->location[1] = player->start.y * BLOCKSIZE + BLOCKSIZE / 2;
	return (player);
}

void	set_color(mlx_image_t *image, int *value, size_t size)
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
		image->pixels[i] = 255;
		i += sizeof(int8_t);
	}
}

mlx_image_t	*get_background(mlx_t *mlx, t_data **head, int flag)
{
	mlx_image_t	*image;
	t_data		*node;
	int			*value;

	node = find_node(head, flag);
	value = (int *)node->cont;
	image = mlx_new_image(mlx, mlx->width, (mlx->height / 2));
	set_color(image, value,
		image->height * image->width * sizeof(int32_t));
	return (image);
}

t_cub3d	*cub3d_init(mlx_t *mlx, t_data **head)
{
	t_cub3d		*cub3d;

	cub3d = ft_calloc(1, sizeof(t_cub3d));
	cub3d->floor = get_background(mlx, head, F_COLOR);
	cub3d->ceiling = get_background(mlx, head, C_COLOR);
	cub3d->mlx = mlx;
	cub3d->data = head;
	cub3d->player = init_player(head);
	return (cub3d);
}
