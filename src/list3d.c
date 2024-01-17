/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:08:00 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/17 11:08:01 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*find_node(t_data **head, int flag)
{
	t_data	*node;

	if (!head || !*head)
		return (NULL);
	node = *head;
	while (node->flag != flag)
		node = node->next;
	return (node);
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
