/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reader.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:04:18 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 14:36:06 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "vector.h"

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
	if (vec->index == vec->length)
	{
		vec->length *= 2;
		vec->content = ft_realloc(vec->content,
				vec->index * vec->type_size,
				vec->length * vec->type_size);
		if (!vec->content)
			return (false);
	}
	vec->content[vec->index] = str;
	printf("%s\n", vec->content[vec->index]);
	vec->index++;
	return (true);
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
	t_data		*map;
	t_data		*tmp;

	map = read_map_to_struct(fd);
	if (!map)
		return (NULL);
	if (count_flags(&map, FLAG) > MAX_FLAG_SIZE)
		return (/* Clean link list */ NULL);
	if (!_init_vector(&vec, sizeof(char *), 32))
		return (/* Clean link list */ NULL);
	tmp = map;
	while (tmp)
	{
		if (ft_isempty(tmp->content) && tmp->flag == MAP)
			return (_free_vector(&vec), NULL); 
		if (!_append_vector(&vec, tmp->content))
			return (_free_vector(&vec), NULL);
		tmp = tmp->next;
	}
	for (int i = 0; vec.content[i]; i++)
		printf("Map; %s\n", vec.content[i]);
	/* Clean link list */
	return (vec.content);
}
