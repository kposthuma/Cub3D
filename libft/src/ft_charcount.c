/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_charcount.c									 :+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2023/06/01 13:02:59 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/29 13:49:26 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// counts the amount char c occurs in string str
size_t	ft_charcount(const char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

static size_t	skip_quotes(const char *str, size_t i)
{
	size_t	j;

	j = 0;
	if (str[i + j] == '\'')
	{
		j++;
		while (str[i + j] != '\'')
			j++;
	}
	else if (str[i + j] == '\"')
	{
		j++;
		while (str[i + j] != '\"')
			j++;
	}
	return (j);
}

//does the same, but skips over quotation marks
size_t	ft_charcount_quotes(const char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		i += skip_quotes(str, i);
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}
