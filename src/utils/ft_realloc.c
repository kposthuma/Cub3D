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
