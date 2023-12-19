/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 19:00:02 by koen          #+#    #+#                 */
/*   Updated: 2023/12/19 15:35:15 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	destroy_cub3d(t_cub3d *cub3d)
{
	clear_list_post(cub3d->mlx, cub3d->data);
	mlx_terminate(cub3d->mlx);
	free(cub3d);
}
