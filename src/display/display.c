/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:07:48 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 12:41:56 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	determine_tex_start(t_ray ray, uint32_t width)
{
	float	temp;

	if (ray.wall == NORTH || ray.wall == SOUTH)
		temp = ray.x / (float)BLOCK;
	else
		temp = ray.y / (float)BLOCK;
	temp = temp - floor(temp);
	return ((size_t)(temp * width));
}

uint32_t	get_pixel(mlx_texture_t *tex, size_t x, size_t y)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (x >= tex->width || y >= tex->height)
		return (0x00000000);
	r = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	g = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel + 1];
	b = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel + 2];
	a = tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel + 3];
	return (ft_get_rgba(r, g, b, a));
}

void	draw_screen(mlx_image_t *screen, t_ray *rays, t_wall *wall, uint32_t ht)
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
		h = 0;
		tex = wall->direction[rays[r].wall];
		scale = (float)tex->height / (float)rays[r].wall_height;
		while (h < rays[r].wall_height)
		{
			tex_start = determine_tex_start(rays[r], tex->width);
			if (h + ((ht / 2) - rays[r].wall_height / 2) >= 0
				&& h + ((ht / 2) - rays[r].wall_height / 2) < ht)
				mlx_put_pixel(screen, r, (ht / 2 - rays[r].wall_height / 2) + h,
						get_pixel(tex, tex_start, (h + 1) * scale));
			h++;
		}
		r++;
	}
}

void	redisplay(t_cub3d *cub3d)
{
	init_rays(cub3d->screen, cub3d->player, (char **)cub3d->map->map->cont);
	draw_screen(cub3d->screen, cub3d->player->ray,
		cub3d->map->walls, cub3d->screen->height);
	cub3d->player->dx = 0;
	cub3d->player->dy = 0;
}
