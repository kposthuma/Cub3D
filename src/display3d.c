/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 11:17:39 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/30 16:07:47 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	_redisplay(t_cub3d *cub3d)
{
	cub3d->player->test->instances->x += cub3d->player->dx;
	cub3d->player->test->instances->y += cub3d->player->dy;
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
