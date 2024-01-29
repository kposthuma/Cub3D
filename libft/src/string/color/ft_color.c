/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_color.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 15:03:14 by cbijman       #+#    #+#                 */
/*   Updated: 2024/01/29 11:20:58 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	_is_color(int c)
{
	if (c >= 0 && c <= 255)
		return (1);
	return (0);
}

t_color	*ft_newcolor(int r, int g, int b, int a)
{
	t_color	*color;

	if (!_is_color(r) || !_is_color(g) || !_is_color(b) || !_is_color(a))
		return (NULL);
	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
	return (color);
}
