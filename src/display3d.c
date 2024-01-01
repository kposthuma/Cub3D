/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 11:17:39 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/01 17:19:19 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	display_raydots(t_cub3d *cub3d)
{
	(void)cub3d;
}

void	_redisplay(t_cub3d *cub3d)
{
	display_raydots(cub3d);
	cub3d->player->test->instances->x = cub3d->player->location[0];
	cub3d->player->test->instances->y = cub3d->player->location[1];
	cub3d->player->dx = 0;
	cub3d->player->dy = 0;
}


void	redisplay(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (cub3d->player->dx != 0 || cub3d->player->dy != 0)
		_redisplay(cub3d);
}
