/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3d.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 17:25:18 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/21 17:42:08 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	trim_nl(char *str)
{
	if (str[ft_strlen(str) - 1] == '\n')
		str[ft_strlen(str) - 1] = '\0';
}
