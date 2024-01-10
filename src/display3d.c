/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 11:17:39 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/10 15:35:17 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// void	display_raydots(t_cub3d *cub3d)
// {
// 	init_rays(cub3d->player,
// 		(char **)((find_node(cub3d->data, MAP_START))->cont));
// 	for (size_t r = 0; r < RAYS; r++)
// 	{
// 		cub3d->player->raydot->instances[r].x = cub3d->player->ray[r]->x;
// 		cub3d->player->raydot->instances[r].y = cub3d->player->ray[r]->y;
// 	}
// }
static void	_init_rays(t_player *player, char **map)
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
		player->ray[i].x = player->ray[i].len * cos(player->ray[i].angle);
		player->ray[i].y = player->ray[i].len * sin(player->ray[i].angle);
		player->ray[i].x += player->location[0];
		player->ray[i].y += player->location[1];
		player->ray[i].wall_height
			= (float)BLOCKSIZE / player->ray[i].corr_len * 1000;
		i++;
	}
}

void	_redisplay(t_cub3d *cub3d)
{
	_init_rays(cub3d->player,
		(char **)((find_node(cub3d->data, MAP_START))->cont));
	test_draw_slices(cub3d->mlx, cub3d->player);
	cub3d->player->dx = 0;
	cub3d->player->dy = 0;
	cub3d->moved = false;
}

void	redisplay(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (cub3d->moved == true)
		_redisplay(cub3d);
}
