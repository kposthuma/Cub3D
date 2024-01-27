/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:07:48 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/27 11:24:05 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	determine_tex_start(t_ray ray, uint32_t width)
{
	float	temp;

	if (ray.wall == NORTH || ray.wall == SOUTH)
		temp = ray.x / (float)BLOCK;
	else
		temp = ray.y / (float)BLOCK;
	temp = temp - floor(temp);
	if (ray.wall == NORTH || ray.wall == EAST)
		return ((size_t)(temp * width));
	else
		return ((size_t)((1 - temp) * width));
}

static uint32_t	get_pixel(mlx_texture_t *tex, size_t x, size_t y)
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

static void	draw_screen(mlx_image_t *scr, t_ray *rays,
	t_wall *wall, size_t count)
{
	size_t			r;
	size_t			h;
	mlx_texture_t	*tex;
	float			scale;
	size_t			tex_start;

	r = 0;
	ft_bzero(scr->pixels, scr->height * scr->width * sizeof(uint32_t));
	while (r < count)
	{
		h = 0;
		tex = wall->direction[rays[r].wall];
		scale = (float)tex->height / (float)rays[r].wall_ht;
		while (h < rays[r].wall_ht)
		{
			tex_start = determine_tex_start(rays[r], tex->width);
			if (h + ((scr->height / 2) - rays[r].wall_ht / 2) >= 0
				&& h + ((scr->height / 2) - rays[r].wall_ht / 2) < scr->height)
				mlx_put_pixel(scr, r, (scr->height / 2 - rays[r].wall_ht / 2)
					+ h, get_pixel(tex, tex_start, (h + 1) * scale));
			h++;
		}
		r++;
	}
}

void	redisplay(t_cub3d *cub3d)
{
	init_rays(cub3d->screen, cub3d->player, cub3d->map->map);
	draw_screen(cub3d->screen, cub3d->player->ray,
		cub3d->map->walls, cub3d->player->raycount);
	cub3d->player->dx = 0;
	cub3d->player->dy = 0;
}
