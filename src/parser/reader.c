#include "cub3d.h"
#include "vector.h"
#include "libft.h"

static bool	init_vector(t_vector *vec, int type_size, int size)
{
	vec->index = 0;
	vec->length = size;
	vec->type_size = type_size;
	vec->content = ft_calloc(vec->length, type_size);
	if (!vec->content)
		return (false);
	return (true);
}

static bool	append_vector(t_vector *vec, char *str)
{
	size_t	i;

	i = 0;
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
	vec->content[vec->index] = ft_strtrim(&str[i], "\n");
	if (!vec->content[vec->index])
		return (false);
	vec->index++;
	return (true);
}

static void	free_vector(t_vector *vec)
{
	free(vec->content);
	vec->content = NULL;
	vec->type_size = 0;
	vec->index = 0;
	vec->length = 0;
}

char	**read_from_file(int fd)
{
	t_vector	vec;
	char		*str;

	if (fd < 0)
		return (NULL);
	if (!init_vector(&vec, sizeof(char *), 32))
		return (NULL);
	str = ft_strdup("\0");
	if (!str)
		return (free_vector(&vec), NULL);
	while (str)
	{
		str = get_next_line(fd);
		if (!str || ft_isempty(str))
		{
			free(str);
			continue ;
		}
		if (!append_vector(&vec, str))
			return (free_vector(&vec), NULL);
		free(str);
	}
	return (vec.content);
}
