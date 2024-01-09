/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag3d.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 17:48:16 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/09 14:14:23 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	_assign_flag(t_data *temp, char *str)
{
	if (*str == '\0')
		temp->flag = TO_CLEAR;
	else if (ft_strncmp(str, "NO ", 3) == 0)
		temp->flag = N_TEXTURE;
	else if (ft_strncmp(str, "SO ", 3) == 0)
		temp->flag = S_TEXTURE;
	else if (ft_strncmp(str, "EA ", 3) == 0)
		temp->flag = E_TEXTURE;
	else if (ft_strncmp(str, "WE ", 3) == 0)
		temp->flag = W_TEXTURE;
	else if (ft_strncmp(str, "F ", 2) == 0)
		temp->flag = F_COLOR;
	else if (ft_strncmp(str, "C ", 2) == 0)
		temp->flag = C_COLOR;
	else
		temp->flag = MAP_START;
}

void	assign_flag(t_data **head)
{
	t_data	*temp;
	char	*str;

	temp = *head;
	while (temp != NULL && (temp->prev == NULL
			|| temp->prev->flag != MAP_START))
	{
		str = (char *)temp->cont;
		while (*str && ft_isspace(*str) == 1)
			str++;
		_assign_flag(temp, str);
		temp = temp->next;
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

bool	count_flag(t_data **head)
{
	int		i;
	size_t	check;
	t_data	*node;

	i = C_COLOR;
	while (i <= MAP_START)
	{
		node = *head;
		check = 0;
		while (node != NULL && (node->prev == NULL
				|| node->prev->flag != MAP_START))
		{
			if (node->flag == i)
				check++;
			node = node->next;
		}
		if (check != 1)
			return (false);
		i++;
	}
	return (true);
}
