/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 19:00:02 by koen          #+#    #+#                 */
/*   Updated: 2024/01/11 23:16:45 by root          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	destroy_player(t_cub3d *cub3d)
{
	free(cub3d->player);
}

void	destroy_cub3d(t_cub3d *cub3d)
{
	clear_list_post(cub3d->mlx, cub3d->data);
	destroy_player(cub3d);
	mlx_delete_image(cub3d->mlx, cub3d->ceiling);
	mlx_delete_image(cub3d->mlx, cub3d->floor);
	mlx_terminate(cub3d->mlx);
	free(cub3d);
}

void	clear_list_pre(t_data **head)
{
	t_data	*temp;
	t_data	*node;

	node = *head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free((char *)temp->cont);
		free(temp);
	}
	free(head);
}

void	clear_list_two(t_data **head)
{
	t_data	*temp;
	t_data	*node;

	node = *head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (temp->flag == MAP_START)
			ft_free((char **)temp->cont);
		else
			free((char *)temp->cont);
		free(temp);
	}
	free(head);
}

void	clear_list_three(t_data **head)
{
	t_data	*temp;
	t_data	*node;

	node = *head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (node->flag >= N_TEXTURE && node->flag <= W_TEXTURE
			&& node->cont != NULL)
			mlx_delete_texture(((t_img_data *)node->cont)->texture);
		if (temp->flag == MAP_START)
			ft_free((char **)temp->cont);
		else
			free((char *)temp->cont);
		free(temp);
	}
	free(head);
}

static void	free_cont(mlx_t *mlx, t_data *node)
{
	if (node->flag >= N_TEXTURE && node->flag <= W_TEXTURE)
	{
		mlx_delete_texture(((t_img_data *)node->cont)->texture);
		mlx_delete_image(mlx, ((t_img_data *)node->cont)->image);
		free((t_img_data *)node->cont);
	}
	else if (node->flag == MAP_START)
		ft_free((char **)node->cont);
	else if (node->flag == C_COLOR || node->flag == F_COLOR)
		free((int *)node->cont);
	else
		free((char *)node->cont);
}

void	clear_list_post(mlx_t *mlx, t_data **head)
{
	t_data	*node;
	t_data	*temp;

	node = *head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free_cont(mlx, temp);
		free(temp);
	}
	free(head);
}
