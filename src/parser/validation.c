/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:04:13 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/23 13:33:29 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cuberr.h"
#include "libft.h"
#include "flags.h"

/*

	Werkt niet helemaal, Het validate nu nog steeds flags die beginnen
	met een getal, zoals 1 en/of 0.
*/
static int	_validate_all_flags(char **map)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		if (!is_flag(&map[i][j]) && !ft_isdigit(map[i][j]))
			return (0);
		i++;
	}
	return (1);
}

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
static int	_validate_duplicate_flags(char **map)
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
	if (!find_player(map))
		return (0);
	if (!check_map(map))
		return (0);
	return (1);
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
	char	**test_map;

	if (!ft_accesstype(filename, MAP_FILE_TYPE))
		return (cuberr(INVALID_FILE), NULL);
	map = read_from_file(open(filename, O_RDONLY));
	if (!map)
		return (cuberr(INVALID_MAP), NULL);
	if (!_validate_all_flags(map))
		return (cuberr(WEIRD_FLAGS), ft_free(map), NULL);
	if (!_validate_duplicate_flags(map))
		return (cuberr(INVALID_FLAGS), ft_free(map), NULL);
	if (!_validate_textures(map))
		return (cuberr(INVALID_TEXTURE_FILES), ft_free(map), NULL);
	test_map = ft_arrdup(&map[6]);
	if (!test_map)
		return (cuberr(SPARERIB_EXPRESS), ft_free(map), NULL);
	if (!_validate_map(test_map))
		return (cuberr(INVALID_MAP),
			ft_free(map), ft_free(test_map),
			NULL);
	ft_free(test_map);
	return (map);
}
