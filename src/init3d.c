/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 18:51:06 by koen          #+#    #+#                 */
/*   Updated: 2024/01/03 18:43:16 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_ray_coordinates(t_player *player, size_t i)
{
	// float	temp;

	player->ray[i].x = player->ray[i].len * sin(player->ray[i].angle);
	// if (player->ray[i].angle < PI)
	// 	player->ray[i].x *= -1;
	player->ray[i].y = player->ray[i].len * cos(player->ray[i].angle);
	if (player->ray[i].angle > PI / 2 || player->ray[i].angle < (3 * PI / 2))
		player->ray[i].y *= -1;
	player->ray[i].x += player->location[0];
	player->ray[i].y += player->location[1];
}

void	init_rays(t_player *player, char **map)
{
	size_t	i;

	i = 0;
	while (i < RAYS)
	{
		player->ray[i].angle
			= (player->angle + ((float)i / (float)RAYS * PI / 3)) - (PI / 6);
		if (player->ray[i].angle < 0)
			player->ray[i].angle += (2 * PI);
		if (player->ray[i].angle > (2 * PI))
			player->ray[i].angle -= (2 * PI);
		player->ray[i].len = ray_len(player, i, map);
		printf("ray[%lu].len <%f>\n", i, player->ray[i].len);
		init_ray_coordinates(player, i);
		i++;
	}
}

float	determine_angle(char **map, t_location loc)
{
	if (map[loc.y][loc.x] == 'N')
		return (0);
	if (map[loc.y][loc.x] == 'E')
		return (PI / 2);
	if (map[loc.y][loc.x] == 'S')
		return (PI);
	if (map[loc.y][loc.x] == 'W')
		return (3 * PI / 2);
	else
		return (-1);
}

t_player	*init_player(t_data **head)
{
	char		**map;
	t_player	*player;

	map = (char **)(find_node(head, MAP_START))->cont;
	player = ft_calloc(1, sizeof(t_player));
	player->start = find_loc(map, "NESW");
	player->angle = determine_angle(map, player->start);
	player->location[0] = player->start.x * BLOCKSIZE + BLOCKSIZE / 2;
	player->location[1] = player->start.y * BLOCKSIZE + BLOCKSIZE / 2;
	player->dx = 0;
	player->dy = 0;
	init_rays(player, map);
	return (player);
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
	cub3d->moved = false;
	return (cub3d);
}
