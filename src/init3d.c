/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 18:51:06 by koen          #+#    #+#                 */
/*   Updated: 2023/12/18 18:56:21 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_cub3d	*cub3d_init(mlx_t *mlx, t_data **head)
{
	t_cub3d	*cub3d;

	cub3d = ft_calloc(1, sizeof(t_cub3d));
	cub3d->mlx = mlx;
	cub3d->data = head;
	return (cub3d);
}