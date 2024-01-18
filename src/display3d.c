/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:07:48 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/18 13:36:21 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//make sure to apply texture correclty depending on whether wall is higher than
// //screen size or inside the drawing plane
// void	draw_slices(mlx_t *mlx, t_player *player)
// {
// 	int			val[3];
// 	uint32_t	height;

// 	for (size_t r = 0; r < RAYS; r++)
// 	{
// 		if (player->ray[r].wall_height > HEIGHT)
// 			height = HEIGHT;
// 		else
// 			height = player->ray[r].wall_height;
// 		player->ray[r].slice_new = mlx_new_image(mlx, (WIDTH / RAYS), height);
// 		if (!player->ray[r].slice_new)
// 			return ((void) ft_printf("Cannot mkae new image\n"));
// 		if (player->ray[r].wall == NORTH)
// 		{
// 			val[0] = 250;
// 			val[1] = 0;
// 			val[2] = 0;
// 		}
// 		else if (player->ray[r].wall == EAST)
// 		{
// 			val[0] = 0;
// 			val[1] = 250;
// 			val[2] = 0;
// 		}
// 		else if (player->ray[r].wall == SOUTH)
// 		{
// 			val[0] = 0;
// 			val[1] = 0;
// 			val[2] = 250;
// 		}
// 		else
// 		{
// 			val[0] = 20;
// 			val[1] = 20;
// 			val[2] = 20;
// 		}
// 		set_color(player->ray[r].slice_new, val, WIDTH / RAYS
// 			* (size_t)height * sizeof(int32_t));
// 		mlx_image_to_window(mlx, player->ray[r].slice_new,
// 			(r * (WIDTH / RAYS)), HEIGHT / 2 - height / 2);
// 	}
// 	for (size_t r = 0; r < RAYS; r++)
// 	{
// 		mlx_delete_image(mlx, player->ray[r].slice_old);
// 		player->ray[r].slice_old = player->ray[r].slice_new;
// 	}
// }

size_t	determine_tex_start(float pos, uint32_t width)
{
	float	temp;

	temp = pos / (float)BLOCKSIZE;
	// printf("pos <%f>, temp <%f>, width <%u>\n", pos, temp, width);
	temp = temp - floor(temp);
	return ((size_t)(temp * width));
}

uint32_t	get_pixel(mlx_texture_t *tex, size_t x, size_t y, size_t ray)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	// if (ray == 0)
	// 	printf("last should be same <%zu> <%d>\n<%lu>\n", y, tex->height, x);
	// if (y == 0)
	// 	printf("highest should be same <%lu> <%u>\n", x, tex->width);
	r = tex->pixels[y * x * tex->bytes_per_pixel];
	g = tex->pixels[y * x * tex->bytes_per_pixel + 1];
	b = tex->pixels[y * x * tex->bytes_per_pixel + 2];
	a = tex->pixels[y * x * tex->bytes_per_pixel + 3];
	return (get_rgba(r, g, b, a));
}

// get_pixel(tex, scale, tex_start, h)
void	draw_screen(mlx_image_t *screen, t_ray *rays, t_data **data)
{
	size_t			r;
	size_t			h;
	mlx_texture_t	*tex;
	float			scale;
	size_t			tex_start;

	r = 0;
	ft_bzero(screen->pixels, screen->height * screen->width * sizeof(uint32_t));
	while (r < RAYS)
	{
		tex = (mlx_texture_t *)((find_node(data, rays[r].wall))->cont);
		scale = (float)tex->height / rays[r].wall_height;
		if (rays[r].wall == NORTH || rays[r].wall == SOUTH)
			tex_start = determine_tex_start(rays[r].x, tex->width);
		else
			tex_start = determine_tex_start(rays[r].y, tex->width);
		h = 0;
		while (h < rays[r].wall_height)
		{
			if (h + (HEIGHT / 2 - rays[r].wall_height / 2) >= 0
				&& h + (HEIGHT / 2 - rays[r].wall_height / 2) < HEIGHT)
			{
				mlx_put_pixel(screen, r,
					(HEIGHT / 2 - rays[r].wall_height / 2) + h,
					get_pixel(tex, tex_start, h * scale, r));
			}
			h++;
		}
		r++;
	}
}

void	redisplay(t_cub3d *cub3d)
{
	init_rays(cub3d->player, (char **)cub3d->map->map->cont);
	draw_screen(cub3d->screen, cub3d->player->ray, &cub3d->map->flags);
	// draw_slices(cub3d->mlx, cub3d->player);
	cub3d->player->dx = 0;
	cub3d->player->dy = 0;
}
