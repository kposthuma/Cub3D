/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 18:51:06 by koen          #+#    #+#                 */
/*   Updated: 2023/12/19 18:28:25 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

mlx_image_t	*get_ceiling(mlx_t *mlx, t_data **head)
{
	mlx_image_t	*ceiling;
	t_data		*node;
	int			rgba;
	int			*value;

	node = *head;
	while (node->flag != C_COLOR)
		node = node->next;
	value = (int *)node->cont;
	ft_printf("ceiling value?<%i><%i><%i>\n", value[0], value[1], value[2]);
	rgba = get_rgba(value[0], value[1], value[2], 0);
	ft_printf("rgba value?<%i>\n", rgba);
	ceiling = mlx_new_image(mlx, mlx->width, (mlx->height / 2));
	ft_memset(ceiling->pixels, 255, ceiling->height * ceiling->width * sizeof(int32_t));
	mlx_image_to_window(mlx, ceiling, 0, 0);
	return (ceiling);
}

mlx_image_t	*get_floor(mlx_t *mlx, t_data **head)
{
	mlx_image_t	*floor;
	t_data		*node;
	int			rgba;
	int			*value;

	node = *head;
	while (node->flag != F_COLOR)
		node = node->next;
	value = (int *)node->cont;
	ft_printf("floor value?<%i><%i><%i>\n", value[0], value[1], value[2]);
	rgba = get_rgba(value[0], value[1], value[2], 0);
	ft_printf("rgba value?<%i>\n", rgba);
	floor = mlx_new_image(mlx, mlx->width, mlx->height / 2 + 1);
	ft_memset(floor->pixels, 200, floor->height * floor->width * sizeof(int32_t));
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
// int32_t	main(void)
// {
//     // Init mlx with a canvas size of 256x256 and the ability to resize the window.
//     mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
    
//     if (!mlx) exit(EXIT_FAILURE);

//     // Create a 128x128 image.
//     mlx_image_t* img = mlx_new_image(mlx, 128, 128);

//     // Set the channels of each pixel in our image to the maximum byte value of 255. 
//     memset(img->pixels, 255, img->width * img->height * BPP);

//     // Draw the image at coordinate (0, 0).
//     mlx_image_to_window(mlx, img, 0, 0);

//     // Run the main loop and terminate on quit.  
//     mlx_loop(mlx);
//     mlx_terminate(mlx);

//     return (EXIT_SUCCESS);
// }
