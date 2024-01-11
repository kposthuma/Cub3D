/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   display3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/30 11:17:39 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/11 14:13:07 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

//make sure to apply texture correclty depending on whether wall is higher than
//screen size or inside the drawing plane
void	draw_slices(mlx_t *mlx, t_player *player)
{
	int	val[3];

	for (size_t r = 0; r < RAYS; r++)
	{
		player->ray[r].slice_new = mlx_new_image(mlx, (uint32_t)(WIDTH / RAYS),
				(uint32_t)roundf(player->ray[r].wall_height));
		if (player->ray[r].wall == NORTH){
			val[0] = 250; val[1] =  250 / (player->ray[r].corr_len / 100); val[2] =  250 / (player->ray[r].corr_len / 100);}
		else if (player->ray[r].wall == EAST){
			val[0] = 250 / (player->ray[r].corr_len / 100); val[1] = 250; val[2] = 250 / (player->ray[r].corr_len / 100);}
		else if (player->ray[r].wall == SOUTH){
			val[0] = 250 / (player->ray[r].corr_len / 100); val[1] = 250 / (player->ray[r].corr_len / 100); val[2] = 250;}
		else{
			val[0] = 250 / (player->ray[r].corr_len / 100); val[1] = 250 / (player->ray[r].corr_len / 100); val[2] = 250 / (player->ray[r].corr_len / 100);}
		set_color(player->ray[r].slice_new, val, WIDTH / RAYS
			* (size_t)player->ray[r].wall_height * sizeof(int32_t));
		mlx_image_to_window(mlx, player->ray[r].slice_new,
			(r * (WIDTH / RAYS)), HEIGHT / 2 - player->ray[r].wall_height / 2);
	}
	for (size_t r = 0; r < RAYS; r++)
	{
		mlx_delete_image(mlx, player->ray[r].slice_old);
		player->ray[r].slice_old = player->ray[r].slice_new;
	}
}

static void	_init_rays(t_player *player, char **map)
{
	size_t	i;

	i = 0;
	while (i < RAYS)
	{
		player->ray[i].angle
			= (player->angle + ((float)i / (float)RAYS * PI / 3)) - (PI / 6);
		if (player->ray[i].angle < 0)
			player->ray[i].angle += (2 * PI);
		if (player->ray[i].angle > (2 * PI))
			player->ray[i].angle -= (2 * PI);
		player->ray[i].len = ray_len(player, i, map);
		player->ray[i].corr_len = player->ray[i].len
			* cos((((float)i / (float)RAYS * PI / 3) - (PI / 6)));
		player->ray[i].x = player->ray[i].len * cos(player->ray[i].angle);
		player->ray[i].y = player->ray[i].len * sin(player->ray[i].angle);
		player->ray[i].x += player->location[0];
		player->ray[i].y += player->location[1];
		player->ray[i].wall_height = ((float)(HEIGHT * PI)
				/ player->ray[i].corr_len) * (player->plane_dist);
		if (player->ray[i].wall_height > HEIGHT)
			player->ray[i].wall_height = HEIGHT;
		i++;
	}
}

void	_redisplay(t_cub3d *cub3d)
{
	_init_rays(cub3d->player,
		(char **)((find_node(cub3d->data, MAP_START))->cont));
	draw_slices(cub3d->mlx, cub3d->player);
	cub3d->player->dx = 0;
	cub3d->player->dy = 0;
	cub3d->moved = false;
}

void	redisplay(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	if (cub3d->moved == true)
		_redisplay(cub3d);
}
