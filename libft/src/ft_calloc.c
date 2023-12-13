/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_calloc.c										:+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2022/10/04 12:59:45 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/29 13:49:26 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*a;
	size_t	i;

	i = 0;
	a = (char *)malloc(count * size);
	if (!a)
		return (NULL);
	while (i < (count * size))
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}
