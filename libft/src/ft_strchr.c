/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_strchr.c										:+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2022/10/04 12:59:20 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/29 13:49:26 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
// The strchr() function locates the first occurrence of c (converted to a char)
// in the string pointed to by s.  The terminating null character is considered 
// to be part of the string; therefore if c is `\0', the functions locate the 
// terminating `\0'.

// The functions strchr() and strrchr() return a pointer to the located 
// character, or NULL if the character does not appear in the string.
char	*ft_strchr(const char *s, int c)
{
	char			*s_cpy;
	unsigned char	x;
	size_t			i;
	size_t			j;

	s_cpy = (char *)s;
	x = c;
	i = 0;
	j = ft_strlen(s_cpy) + 1;
	while (i < j)
	{
		if (s_cpy[i] == x)
			return (&s_cpy[i]);
		i++;
	}
	return (NULL);
}
