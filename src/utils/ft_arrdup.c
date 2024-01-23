/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 14:44:17 by cbijman       #+#    #+#                 */
/*   Updated: 2024/01/23 13:33:29 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	_free_array(char **arg)
{
	size_t	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i])
			free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
	arg = NULL;
}

char	**ft_arrdup(char **arr)
{
	size_t	i;
	char	**narr;

	if (!arr || !*arr)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	narr = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (arr[i])
	{
		narr[i] = ft_strdup(arr[i]);
		if (!narr[i])
			_free_array(narr);
		i++;
	}
	narr[i] = NULL;
	return (narr);
}
