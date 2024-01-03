/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 11:17:39 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/03 17:33:03 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	display_raydots(t_cub3d *cub3d)
{
	init_rays(cub3d->player,
		(char **)((find_node(cub3d->data, MAP_START))->cont));
	for (size_t r = 0; r < RAYS; r++)
	{
		cub3d->player->raydot->instances[r].x = cub3d->player->ray[r].x;
		cub3d->player->raydot->instances[r].y = cub3d->player->ray[r].y;
	}
}

void	_redisplay(t_cub3d *cub3d)
{
	display_raydots(cub3d);
	cub3d->player->test->instances[0].x = (cub3d->player->location[0]
			- BLOCKSIZE / 20);
	cub3d->player->test->instances[0].y = (cub3d->player->location[1]
			- BLOCKSIZE / 20);
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
