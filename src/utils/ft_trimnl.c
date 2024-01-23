/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_trimnl.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 18:19:31 by cbijman       #+#    #+#                 */
/*   Updated: 2024/01/23 13:33:29 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_trimnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		i++;
	if (str[i - 1] == '\n')
		str[i - 1] = '\0';
}
