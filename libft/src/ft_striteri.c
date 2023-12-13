/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_striteri.c									  :+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2022/10/05 13:00:27 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/29 13:49:26 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	char			*s_cpy;

	i = 0;
	s_cpy = (char *)s;
	while (s_cpy[i])
	{
		f(i, &s_cpy[i]);
		i++;
	}
}
