/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_access.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:03:24 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 13:33:29 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if a file can be accessed.
 *
 * This function attempts to open the specified file in read-only mode.
 * If the file can be opened successfully, it is closed and the
 * function returns 1. Otherwise, the function returns 0.
 *
 * @param filename The name of the file to be checked.
 * @return 1 if the file can be accessed, 0 otherwise.
 */
int	ft_access(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
