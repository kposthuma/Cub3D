/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:07:48 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/18 15:11:30 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	determine_tex_start(t_ray ray, uint32_t width)
{
	float	temp;

	if (ray.wall == NORTH || ray.wall == SOUTH)
		temp = ray.x / (float)BLOCKSIZE;
	else
		temp = ray.y / (float)BLOCKSIZE;
	temp = temp - floor(temp);
	return ((size_t)(temp * width));
}

uint32_t	get_pixel(mlx_texture_t *tex, size_t x, size_t y)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (x < tex->width && y < tex->height)
	{
		r = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
		g = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel + 1];
		b = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel + 2];
		a = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel + 3];
		return (get_rgba(r, g, b, a));
	}
	else
		return (get_rgba(0, 0, 0, 0));
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
		tex_start = determine_tex_start(rays[r], tex->width);
		h = 0;
		while (h < rays[r].wall_height)
		{
			if (h + (HEIGHT / 2 - rays[r].wall_height / 2) >= 0
				&& h + (HEIGHT / 2 - rays[r].wall_height / 2) < HEIGHT)
				mlx_put_pixel(screen, r,
					(HEIGHT / 2 - rays[r].wall_height / 2) + h,
					get_pixel(tex, tex_start, (h + 1) * scale));
			h++;
		}
		r++;
	}
}

void	redisplay(t_cub3d *cub3d)
{
	init_rays(cub3d->player, (char **)cub3d->map->map->cont);
	draw_screen(cub3d->screen, cub3d->player->ray, &cub3d->map->flags);
	cub3d->player->dx = 0;
	cub3d->player->dy = 0;
}
