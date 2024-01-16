#include "cub3d.h"
#include "libft.h"

/**
 * Reallocates a memory block with a new size.
 *
 * @param ptr The pointer to the memory block to be reallocated.
 * @param oldsize The current size of the memory block.
 * @param size The new size of the memory block.
 * @return A pointer to the memory block, or NULL if the realloc fails.
 */
void	*ft_realloc(void *ptr, size_t oldsize, size_t size)
{
	void	*nptr;

	if (!ptr)
		return (NULL);
	if (oldsize == size)
		return (ptr);
	if (oldsize > size)
		oldsize = size;
	nptr = malloc(size);
	if (!nptr)
		return (free(ptr), NULL);
	ft_bzero(nptr, size);
	ft_memcpy(nptr, ptr, oldsize);
	free(ptr);
	return (nptr);
}
