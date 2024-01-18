/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:08:04 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/18 16:38:36 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d	cub3d;
	t_map	*data;
	mlx_t	*mlx;

	if (ac != 2)
		return (1);
	data = read_map_from_file(av[1]);
	if (!data)
		return (1);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!mlx)
		return (1);
	if (!cub3d_init(&cub3d, mlx, data))
		return (1);
	init_window(&cub3d);
	destroy_cub3d(&cub3d);
	return (EXIT_SUCCESS);
}
