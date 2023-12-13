/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_split_whitespace.c							  :+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2023/06/22 12:54:30 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/31 15:34:32 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	incrementer(char *str, size_t j)
{
	size_t	i;

	i = j;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i])
			i++;
	}
	else if (str[i] == '\"' && str[i])
	{
		i++;
		while (str[i] != '\"' && str[i])
			i++;
	}
	return (i - j);
}

static size_t	ft_length(char *str, size_t i)
{
	size_t	len;

	len = 0;
	while (ft_isspace(str[i]) == 0 && str[i])
	{
		len += incrementer(str, i);
		len++;
		i += incrementer(str, i);
		i++;
	}
	return (len);
}

static char	**fillup_split(char **split, char *s_cpy, size_t words)
{
	size_t	j;
	size_t	i;
	size_t	len;

	j = 0;
	i = 0;
	while (j < (words - 1))
	{
		while (ft_isspace(s_cpy[i]) == 1)
			i++;
		len = ft_length(s_cpy, i);
		split[j] = ft_substr(s_cpy, i, len);
		if (!split[j])
			return (ft_free(split), NULL);
		i += len;
		j++;
	}
	return (split);
}

static size_t	word_count(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] && ft_isspace(str[i]) == 0)
			j++;
		while (str[i] && ft_isspace(str[i]) == 0)
		{
			i += incrementer(str, i);
			i++;
		}
		while (str[i] && ft_isspace(str[i]) == 1)
			i++;
	}
	return (j);
}

char	**ft_split_whitespace(char const *s)
{
	size_t	words;
	char	*s_cpy;
	char	**split;

	s_cpy = (char *)s;
	words = word_count(s_cpy);
	split = ft_calloc(words, sizeof(char *));
	if (!split)
		return (NULL);
	return (fillup_split(split, s_cpy, words));
}

// int	main(int argc, char **argv)
// {
// 	char	**jemoeder;

// 	jemoeder = ft_split_quotes(argv[1], ' ');
// 	print_charpp(jemoeder);
// 	return (argc);
// }