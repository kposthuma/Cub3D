/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 14:59:51 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 13:39:28 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	init_rays(mlx_image_t *screen, t_player *player, char **map)
{
	size_t	i;

	i = 0;
	while (i < RAYS)
	{
		player->ray[i].angle = (player->angle + ((float) i / RAYS * PI / 3))
			- (PI / 6);
		if (player->ray[i].angle < 0)
			player->ray[i].angle += (2 * PI);
		if (player->ray[i].angle > (2 * PI))
			player->ray[i].angle -= (2 * PI);
		player->ray[i].len = ray_len(player, i, map);
		player->ray[i].corr_len = player->ray[i].len
			* cos((((float)i / (float)RAYS * PI / 3) - (PI / 6)));
		player->ray[i].x = player->ray[i].len
			* cos(player->ray[i].angle) + player->location[0];
		player->ray[i].y = player->ray[i].len
			* sin(player->ray[i].angle) + player->location[1];
		player->ray[i].wall_height = (float)(screen->height)
			* PI / player->ray[i].corr_len * (player->plane_dist);
		i++;
	}
}

static float	determine_angle(char **map, t_location loc)
{
	if (!map[loc.y])
		return (-1);
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

static t_player	*init_player(t_cub3d *cub, t_data **head)
{
	t_player	*player;
	char		**map;

	map = (char **)(*head)->cont;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (NULL);
	player->start = find_loc(map, "NESW");
	player->angle = determine_angle(map, player->start);
	if (player->angle < 0)
		return (free(player), NULL);
	player->location[0] = (player->start.x * BLOCK) + (BLOCK / 2);
	player->location[1] = (player->start.y * BLOCK) + (BLOCK / 2);
	player->dx = 0;
	player->dy = 0;
	player->plane_dist = BLOCK / 2;
	init_rays(cub->screen, player, map);
	return (player);
}

static mlx_image_t	*get_background(mlx_t *mlx, t_color *color)
{
	mlx_image_t		*image;

	image = mlx_new_image(mlx, mlx->width, mlx->height / 2);
	if (!image)
		return (NULL);
	set_colorc(image, color, image->height * image->width * sizeof(int32_t));
	return (image);
}

bool	cub3d_init(t_cub3d *cub, mlx_t *mlx, t_map *data)
{
	ft_bzero(cub, sizeof(t_cub3d));
	cub->screen = mlx_new_image(mlx, mlx->width, mlx->height);
	cub->floor = get_background(mlx, data->floor);
	cub->ceiling = get_background(mlx, data->ceiling);
	cub->player = init_player(cub, &data->map);
	if (!cub->player || !cub->screen || !cub->floor || !cub->ceiling)
		return (free(cub->player), mlx_delete_image(mlx, cub->screen),
			mlx_delete_image(mlx, cub->floor),
			mlx_delete_image(mlx, cub->ceiling), false);
	cub->map = data;
	cub->data = &data->map;
	cub->mlx = mlx;
	return (true);
}
