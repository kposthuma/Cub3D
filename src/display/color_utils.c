/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:07:34 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 17:59:34 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_trim_whitespace(char *s)
{
	char	*s2;

	s2 = s;
	while (s2 && *s2)
	{
		if (ft_isspace(*s2))
			s2 = ft_memmove(s2, (s2 + 1), ft_strlen(s2));
		else
			s2++;
	}
	return (s);
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
