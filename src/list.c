/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:08:00 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 14:58:36 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*find_node(t_data **head, t_mapflag flag)
{
	t_data	*node;

	if (!head || !*head)
		return (NULL);
	node = *head;
	while (node && node->flag != flag)
		node = node->next;
	return (node);
}

t_data	*new_node(char *content, t_mapflag flag)
{
	t_data	*node;

	if (!content)
		return (NULL);
	node = malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->content = content;
	node->flag = flag;
	node->next = NULL;
	return (node);
}

void	clear_nodes(t_data **lst)
{
	t_data	*pos;
	t_data	*temp;

	if (!lst)
		return ;
	pos = *lst;
	while (pos)
	{
		temp = pos->next;
		free(pos->content);
		free(pos);
		pos = temp;
	}
	*lst = NULL;
}

void	add_node(t_data **head, t_data *node)
{
	t_data	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
