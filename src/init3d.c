/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 18:51:06 by koen          #+#    #+#                 */
/*   Updated: 2023/12/21 17:47:49 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	set_color(mlx_image_t *image, int *value, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		image->pixels[i] = value[0];
		i += sizeof(int8_t);
		image->pixels[i] = value[1];
		i += sizeof(int8_t);
		image->pixels[i] = value[2];
		i += sizeof(int8_t);
		image->pixels[i] = 255;
		i += sizeof(int8_t);
	}
}

mlx_image_t	*get_ceiling(mlx_t *mlx, t_data **head)
{
	mlx_image_t	*ceiling;
	t_data		*node;
	int			*value;

	node = *head;
	while (node->flag != C_COLOR)
		node = node->next;
	value = (int *)node->cont;
	ceiling = mlx_new_image(mlx, mlx->width, (mlx->height / 2));
	set_color(ceiling, value,
		ceiling->height * ceiling->width * sizeof(int32_t));
	mlx_image_to_window(mlx, ceiling, 0, 0);
	return (ceiling);
}

mlx_image_t	*get_floor(mlx_t *mlx, t_data **head)
{
	mlx_image_t	*floor;
	t_data		*node;
	int			*value;

	node = *head;
	while (node->flag != F_COLOR)
		node = node->next;
	value = (int *)node->cont;
	floor = mlx_new_image(mlx, mlx->width, mlx->height / 2 + 1);
	set_color(floor, value, floor->height * floor->width * sizeof(int32_t));
	mlx_image_to_window(mlx, floor, 0, mlx->height / 2);
	return (floor);
}

t_cub3d	*cub3d_init(mlx_t *mlx, t_data **head)
{
	t_cub3d		*cub3d;

	cub3d = ft_calloc(1, sizeof(t_cub3d));
	cub3d->floor = get_floor(mlx, head);
	cub3d->ceiling = get_ceiling(mlx, head);
	cub3d->mlx = mlx;
	cub3d->data = head;
	mlx_loop(mlx);
	return (cub3d);
}
