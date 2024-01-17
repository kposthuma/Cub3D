/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flags.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:06:45 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/17 11:06:47 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "flags.h"

static int	_compare(char *str, char *flag)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && flag[i])
	{
		if (str[i] != flag[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_flag(char *str)
{
	if (_compare(str, NORTH_FLAG))
		return (1);
	if (_compare(str, SOUTH_FLAG))
		return (1);
	if (_compare(str, WEST_FLAG))
		return (1);
	if (_compare(str, EAST_FLAG))
		return (1);
	if (_compare(str, FLOOR_COLOR_FLAG))
		return (1);
	if (_compare(str, CEILING_COLOR_FLAG))
		return (1);
	return (0);
}

char	*find_flag(char **arr, const char *flag)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(flag);
	while (arr[i])
	{
		if (ft_strncmp(arr[i], flag, len) == 0
			&& ft_isspace(arr[i][len])
			&& !ft_isempty(&arr[i][len])
			&& is_flag(arr[i]))
		{
			while (ft_isspace(arr[i][len]))
				len++;
			return (&arr[i][len]);
		}
		i++;
	}
	return (NULL);
}

int	validate_flag(char **arr, const char *flag)
{
	size_t	i;
	size_t	len;
	int		found;

	i = 0;
	found = 0;
	len = ft_strlen(flag);
	while (arr[i])
	{
		if (found > 1)
			return (0);
		if (ft_strncmp(arr[i], flag, len) == 0
			&& ft_isspace(arr[i][len])
			&& !ft_isempty(&arr[i][len])
			&& is_flag(arr[i]))
			found++;
		i++;
	}
	if (!found)
		return (0);
	return (1);
}
