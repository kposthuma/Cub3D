/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_access.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:03:24 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/24 14:04:01 by kposthum      ########   odam.nl         */
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

/**
 * Validates if the given filename has the specified type.
 *
 * @param arg The filename to be validated.
 * @param type The type of the filename to be checked against.
 * @return 1 if the filename has the specified type, 0 otherwise.
 */
static int	_validate_filename(char *arg, char *type)
{
	size_t	len;
	size_t	type_len;

	len = ft_strlen(arg);
	type_len = ft_strlen(type);
	if (len < type_len)
		return (0);
	if (ft_strncmp(&arg[len - type_len], type, type_len))
		return (0);
	return (1);
}

/**
 * Checks if a file has the expected type.
 *
 * This function validates the filename and checks if the file can be opened
 * with read-only access. It returns 1 if the file has the expected type and
 * can be accessed, and 0 otherwise.
 *
 * @param filename The name of the file to check.
 * @param expected_type The expected type of the file.
 * @return 1 if the file has the expected type and can be accessed, 0 otherwise.
 */
int	ft_accesstype(char *filename, char *expected_type)
{
	int	fd;

	if (!filename)
		return (0);
	if (!_validate_filename(filename, expected_type))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
