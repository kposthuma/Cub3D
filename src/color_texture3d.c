/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_texture3d.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: koen <koen@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/17 16:32:53 by koen          #+#    #+#                 */
/*   Updated: 2023/12/23 20:11:47 by koen          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	validate_value(char **val)
{
	size_t	i;
	size_t	j;

	i = 0;
	val[2][ft_strlen(val[2]) - 1] = '\0';
	while (val[i])
	{
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
	t_data			*node;
	char			*str;
	t_img_data		*img;

	node = *head;
	while (node->flag != flag)
		node = node->next;
	str = (char *)node->cont + 2;
	while (ft_isspace(*str) == 1)
		str++;
	img = ft_calloc(1, sizeof(t_img_data));
	trim_nl(str);
	img->texture = mlx_load_png(str);
	if (!img->texture)
		return (free(img), false);
	free((char *)node->cont);
	node->cont = (void *)img;
	return (true);
}
