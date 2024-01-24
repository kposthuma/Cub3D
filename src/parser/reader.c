/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reader.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:04:18 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/24 16:10:30 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "vector.h"

static bool	is_map(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (false);
	while (ft_isspace(str[i]))
		i++;
	return (str[i] == '1' || str[i] == '0');
}

static bool	_init_vector(t_vector *vec, int type_size, int size)
{
	vec->index = 0;
	vec->length = size;
	vec->type_size = type_size;
	vec->content = ft_calloc(vec->length, type_size);
	if (!vec->content)
		return (false);
	return (true);
}

static bool	_append_vector(t_vector *vec, char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (true);
	if (vec->index == vec->length)
	{
		vec->length *= 2;
		vec->content = ft_realloc(vec->content,
				vec->index * vec->type_size,
				vec->length * vec->type_size);
		if (!vec->content)
			return (false);
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '1' || str[i] == '0')
		i = 0;
	if (ft_isspace(str[ft_strlen(str) - 1]))
		str[ft_strlen(str) - 1] = '\0';
	vec->content[vec->index] = ft_strdup(&str[i]);
	if (!vec->content[vec->index])
		return (false);
	vec->index++;
	return (free(str), true);
}

static void	_free_vector(t_vector *vec)
{
	free(vec->content);
	vec->content = NULL;
	vec->type_size = 0;
	vec->index = 0;
	vec->length = 0;
}

/**
 * Reads data from a file descriptor and stores it in
 * a dynamically allocated array of strings.
 * 
 * @param fd The file descriptor to read from.
 * @return	A pointer to the array of strings containing
 * 			the read data, or NULL if an error occurs.
 */
char	**read_from_file(int fd)
{
	t_vector	vec;
	char		*str;
	static char	*lstr = NULL;
	static bool	map = false;

	if (!_init_vector(&vec, sizeof(char *), 32))
		return (NULL);
	str = "\0";
	while (str)
	{
		str = get_next_line(fd);
		if (is_map(str))
			map = true;
		if (!str || (ft_isempty(str) && map == false))
		{
			free(str);
			continue ;
		}
		if (!_append_vector(&vec, str))
			return (_free_vector(&vec), NULL);
		free(lstr);
		lstr = ft_strdup(str);
	}
	return (free(lstr), vec.content);
}
