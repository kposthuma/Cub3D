/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 16:53:26 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/11 22:55:45 by root          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_cub3d	*cubd;
	mlx_t	*mlx;

	data = read_map_from_file(av[1]);
	if (!data)
		return (1); /* Map couldn't be initialized... */
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!mlx)
		return (1); /* MLX couldn't be initialized... */
	cubd = cub3d_init(mlx, &data);
	if (!cubd)
		return (1); /* Renderer couldn't be initialized... */
	init_window(cubd);
	destroy_cub3d(cubd);
	return (EXIT_SUCCESS);
}
