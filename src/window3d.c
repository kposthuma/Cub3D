/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window3d.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/25 20:11:23 by koen          #+#    #+#                 */
/*   Updated: 2023/12/25 20:17:06 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void test(t_cub3d *cub3d)
{
	mlx_image_to_window(cub3d->mlx, cub3d->ceiling, 0, 0);
	mlx_image_to_window(cub3d->mlx, cub3d->floor, 0, cub3d->mlx->height / 2);
	mlx_loop(cub3d->mlx);
}