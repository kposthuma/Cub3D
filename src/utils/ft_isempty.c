/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isempty.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 13:17:40 by cbijman       #+#    #+#                 */
/*   Updated: 2024/01/10 13:50:48 by cbijman       ########   odam.nl         */
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
