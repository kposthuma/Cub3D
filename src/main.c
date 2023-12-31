/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 16:53:26 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/31 15:39:45 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_data	**head;
	mlx_t	*mlx;
	t_cub3d	*cub3d;

	head = parse_input(argc, argv);
	if (head == NULL)
		return (1);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	cub3d = cub3d_init(mlx, head);
	test(cub3d);
	destroy_cub3d(cub3d);
}
