/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 18:51:06 by koen          #+#    #+#                 */
/*   Updated: 2023/12/23 20:07:10 by koen          ########   odam.nl         */
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

mlx_image_t	*get_background(mlx_t *mlx, t_data **head, bool where, int flag)
{
	mlx_image_t	*image;
	t_data		*node;
	int			*value;

	node = find_node(head, flag);
	value = (int *)node->cont;
	image = mlx_new_image(mlx, mlx->width, (mlx->height / 2));
	set_color(image, value,
		image->height * image->width * sizeof(int32_t));
	if (!where)
		mlx_image_to_window(mlx, image, 0, 0);
	else
		mlx_image_to_window(mlx, image, 0, mlx->height / 2);
	return (image);
}

t_cub3d	*cub3d_init(mlx_t *mlx, t_data **head)
{
	t_cub3d		*cub3d;

	cub3d = ft_calloc(1, sizeof(t_cub3d));
	cub3d->floor = get_background(mlx, head, true, F_COLOR);
	cub3d->ceiling = get_background(mlx, head, false, C_COLOR);
	cub3d->mlx = mlx;
	cub3d->data = head;
	mlx_loop(mlx);
	return (cub3d);
}
