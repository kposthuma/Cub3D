/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:04:13 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/25 15:00:21 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cuberr.h"
#include "libft.h"
#include "flags.h"

/**
 * Validates the textures used in the map.
 * 
 * @param map The map containing the texture flags.
 * @return 1 if all textures are valid, 0 otherwise.
 */
static int	_validate_textures(char **map)
{
	if (!ft_accesstype(find_flag(map, NORTH_FLAG), IMAGE_FILE_TYPE))
		return (0);
	if (!ft_accesstype(find_flag(map, SOUTH_FLAG), IMAGE_FILE_TYPE))
		return (0);
	if (!ft_accesstype(find_flag(map, WEST_FLAG), IMAGE_FILE_TYPE))
		return (0);
	if (!ft_accesstype(find_flag(map, EAST_FLAG), IMAGE_FILE_TYPE))
		return (0);
	return (1);
}

/**
 * Validates the presence of required flags in the map.
 * 
 * @param map The map containing the flags.
 * @return 1 if all required flags are present, 0 otherwise.
 */
static int	_validate_flags(char **map)
{
	if (!validate_flag(map, NORTH_FLAG))
		return (0);
	if (!validate_flag(map, SOUTH_FLAG))
		return (0);
	if (!validate_flag(map, WEST_FLAG))
		return (0);
	if (!validate_flag(map, EAST_FLAG))
		return (0);
	if (!validate_flag(map, FLOOR_FLAG))
		return (0);
	if (!validate_flag(map, CEILING_FLAG))
		return (0);
	return (1);
}

/**
 * Validates the given map.
 * 
 * @param map The map to be validated.
 * @return 1 if the map is valid, 0 otherwise.
 */
static int	_validate_map(char **map)
{
	char **clone;
	
	clone = ft_arrdup(map);
	if (!clone)
		return (0);
	if (find_player(clone) != 1)
		return (ft_arrfree(clone), 0);
	if (!check_map(clone))
		return (ft_arrfree(clone), 0);
	return (ft_arrfree(clone), 1);
}

/**
 * Imports a map from a file.
 *
 * @param filename The name of the file to import the map from.
 * @return The imported map as a 2D array of characters,
	or NULL if there was an error.
 */
char	**import_map(char *filename)
{
	char	**map;

	if (!ft_accesstype(filename, MAP_FILE_TYPE))
		return (cuberr(INVALID_FILE), NULL);
	map = read_from_file(open(filename, O_RDONLY));
	if (!map)
		return (cuberr(INVALID_MAP), NULL);
	if (!_validate_flags(map))
		return (cuberr(INVALID_FLAGS), ft_arrfree(map), NULL);
	if (!_validate_textures(map))
		return (cuberr(INVALID_TEXTURE_FILES), ft_arrfree(map), NULL);
	if (!_validate_map(&map[6]))
		return (cuberr(INVALID_MAP), ft_arrfree(map), NULL);
	return (map);
}
