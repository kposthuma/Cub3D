/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 16:21:27 by cbijman       #+#    #+#                 */
/*   Updated: 2024/01/10 13:28:16 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t oldsize, size_t size)
{
	void	*nptr;

	if (!ptr)
		return (NULL);
	if (oldsize == size)
		return (ptr);
	if (oldsize > size)
		oldsize = size;
	printf("Reallocating size: %zu\n", size);
	nptr = malloc(size);
	if (!nptr)
		return (free(ptr), NULL);
	ft_bzero(nptr, size);
	ft_memcpy(nptr, ptr, oldsize);
	free(ptr);
	return (nptr);
}
