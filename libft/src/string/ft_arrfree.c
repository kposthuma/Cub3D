/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_arrfree.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: root <root@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 01:24:19 by root          #+#    #+#                 */
/*   Updated: 2024/01/25 16:48:18 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_arrfree(char **arr)
{
	size_t	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
