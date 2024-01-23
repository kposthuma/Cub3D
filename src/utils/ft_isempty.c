/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isempty.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:03:06 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 12:38:15 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

/**
 * Checks if a string is empty.
 *
 * @param str The string to check.
 * @return 1 if the string is empty, 0 otherwise.
 */
int	ft_isempty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (*str == '\n' || *str == '\0')
		return (1);
	while (ft_strchr("\t\v\f\r ", str[i]))
		i++;
	if (ft_isprint(str[i]) && str[i] != 32)
		return (0);
	return (1);
}
