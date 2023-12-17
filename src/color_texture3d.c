/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_texture3d.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:32:53 by koen          #+#    #+#                 */
/*   Updated: 2023/12/17 16:41:00 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	validate_color(t_data **head, int flag)
{
	t_data	*node;
	char	*str;
	char	**val;

	node = *head;
	while (node->flag != flag)
		node = node->next;
	str = (char *)node->cont + 1;
	while (ft_isspace(*str) == 1)
		str++;
	val = ft_split(str, ',');
	if (strofstrlen(val) != 3)
		return (false);
}

bool	validate_texture(t_data **head, size_t flag)
{}
