/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 14:59:51 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/18 13:20:40 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
		player->ray[i].corr_len = player->ray[i].len
			* cos((((float)i / (float)RAYS * PI / 3) - (PI / 6)));
		player->ray[i].x = player->ray[i].len * cos(player->ray[i].angle) + player->location[0];
		player->ray[i].y = player->ray[i].len * sin(player->ray[i].angle) + player->location[1];
		// player->ray[i].x += player->location[0];
		// player->ray[i].y += player->location[1];
		player->ray[i].wall_height = (float)(HEIGHT * PI)
			/ player->ray[i].corr_len * (player->plane_dist);
		i++;
	}
}

float	determine_angle(char **map, t_location loc)
{
	if (map[loc.y][loc.x] == 'N')
		return (3 * PI / 2);
	if (map[loc.y][loc.x] == 'E')
		return (0);
	if (map[loc.y][loc.x] == 'S')
		return (PI / 2);
	if (map[loc.y][loc.x] == 'W')
		return (PI);
	else
		return (-1);
}

t_player	*init_player(t_data **head)
{
	t_player	*player;
	char		**map;

	map = (char **)find_node(head, MAP_START)->cont;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->start = find_loc(map, "NESW");
	player->angle = determine_angle(map, player->start);
	player->location[0] = player->start.x * BLOCKSIZE + BLOCKSIZE / 2;
	player->location[1] = player->start.y * BLOCKSIZE + BLOCKSIZE / 2;
	player->dx = 0;
	player->dy = 0;
	player->plane_dist = BLOCKSIZE / 2;
	init_rays(player, map);
	return (player);
}

mlx_image_t	*get_background(mlx_t *mlx, t_data **head, int flag)
{
	const int	*value = (int *)find_node(head, flag)->cont;
	mlx_image_t	*image;

	if (!value)
		return (NULL);
	printf("color values : R%i, G%i, B%i\n", value[0], value[1], value[2]);
	image = mlx_new_image(mlx, mlx->width, (mlx->height / 2));
	if (!image)
		return (NULL);
	set_color(image, (int *)value,
		image->height * image->width * sizeof(int32_t));
	return (image);
}

bool	cub3d_init(t_cub3d *cub, mlx_t *mlx, t_map *data)
{
	ft_memset(cub, 0, sizeof(t_cub3d));
	cub->floor = get_background(mlx, &data->flags, F_COLOR);
	if (!cub->floor)
		return (false);
	cub->ceiling = get_background(mlx, &data->flags, C_COLOR);
	if (!cub->ceiling)
		return (false);
	cub->player = init_player(&data->map);
	if (!cub->player)
		return (false);
	cub->screen = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!cub->screen)
		return (false);
	cub->data = &data->map;
	cub->mlx = mlx;
	cub->map = data;
	return (true);
}
