/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapiteri.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:02:54 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 12:38:15 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Applies a function to each element of a string array, along with its index.
 *
 * @param arr The string array to iterate over.
 * @param f   The function to apply to each element.
 *
 * @return 1 if all iterations were successful, 0 otherwise.
 */
int	ft_strmapiteri(char **arr, int (*f)(char *, int))
{
	size_t	i;

	if (!*arr)
		return (0);
	i = 0;
	while (arr[i])
	{
		if (!f(arr[i], i))
			return (0);
		i++;
	}
	return (1);
}
