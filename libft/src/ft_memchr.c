/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_memchr.c										:+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2022/10/04 12:59:33 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/29 13:49:26 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	x;
	size_t			i;

	i = 0;
	x = c;
	a = (void *)s;
	while (i < n)
	{
		if (a[i] == x)
			return (&a[i]);
		i++;
	}
	return (NULL);
}
