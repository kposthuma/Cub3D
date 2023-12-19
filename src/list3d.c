/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 18:00:15 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/19 15:35:29 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

void	free_cont(mlx_t *mlx, t_data *node)
{
	if (node->flag >= N_TEXTURE && node->flag <= W_TEXTURE)
	{
		mlx_delete_texture(((t_img_data *)node->cont)->texture);
		mlx_delete_image(mlx, ((t_img_data *)node->cont)->image);
		free((t_img_data *)node->cont);
	}
	else if (node->flag == MAP_START)
		ft_free((char **)node->cont);
	else if (node->flag != C_COLOR && node->flag != F_COLOR)
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

t_data	*newnode(void *cont)
{
	t_data	*node;

	node = ft_calloc(1, sizeof(t_data));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->cont = cont;
	return (node);
}

void	clear_node(t_data **head, t_data *node)
{
	t_data	*temp;

	temp = node->next;
	if (node->prev == NULL)
		*head = temp;
	else if (temp != NULL)
	{
		temp->prev = node->prev;
		temp->prev->next = temp;
	}
	free((char *)node->cont);
	free(node);
}

void	add_node(t_data **head, t_data *node)
{
	t_data	*temp;

	temp = *head;
	if (!temp)
		*head = node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
		node->prev = temp;
	}
}

void	set_flag_rest(t_data *node)
{
	node = node->next;
	while (node != NULL)
	{
		node->flag = TO_CLEAR;
		node = node->next;
	}
}
