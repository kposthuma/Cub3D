/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_texture3d.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:07:34 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/18 14:53:26 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "color.h"

void	set_color(mlx_image_t *image, int *color, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		image->pixels[i] = color[0];
		i += sizeof(int8_t);
		image->pixels[i] = color[1];
		i += sizeof(int8_t);
		image->pixels[i] = color[2];
		i += sizeof(int8_t);
		image->pixels[i] = 255;
		i += sizeof(int8_t);
	}
}

void	set_colorc(mlx_image_t *image, t_color *color, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		image->pixels[i] = color->r;
		i += sizeof(int8_t);
		image->pixels[i] = color->g;
		i += sizeof(int8_t);
		image->pixels[i] = color->b;
		i += sizeof(int8_t);
		image->pixels[i] = 255;
		i += sizeof(int8_t);
	}
}

bool	validate_value(char **val)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	val[2][ft_strlen(val[2]) - 1] = '\0';
	while (val[i])
	{
		temp = val[i];
		val[i] = ft_strtrim(val[i], "\t\n\v\f\r ");
		free(temp);
		if (ft_strlen(val[i]) > 3
			|| (ft_atoi(val[i]) > 255 && ft_atoi(val[i]) < 0))
			return (false);
		j = 0;
		while (val[i][j])
		{
			if (ft_isdigit(val[i][j]) == 0)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_color(t_data **head, int flag)
{
	t_data	*node;
	char	*str;
	char	**val;
	int		*arr;
	int		i;

	node = find_node(head, flag);
	str = (char *)node->cont + 1;
	while (ft_isspace(*str) == 1)
		str++;
	val = ft_split(str, ',');
	if (!val || strofstrlen(val) != 3 || !validate_value(val))
		return (ft_free(val), false);
	free((char *)node->cont);
	arr = ft_calloc(3, sizeof(int));
	i = 0;
	while (i < 3)
	{
		arr[i] = ft_atoi(val[i]);
		i++;
	}
	node->cont = (void *)arr;
	return (ft_free(val), true);
}

bool	validate_texture(t_data **head, int flag)
{
	(void)head;
	(void)flag;
	printf("validate_texture called\n");
	return (true);
}
