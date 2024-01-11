#include "cub3d.h"
#include "cuberr.h"
#include "libft.h"

/**
 * Validates the filename by checking if it has the ".cub" extension.
 *
 * @param arg The filename to be validated.
 * @return 0 if the filename is valid, 1 otherwise.
 */
static int	_validate_filename(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 4)
		return (0);
	if (ft_strncmp(&arg[len - 4], ".cub", 4))
		return (0);
	if (!ft_access(arg))
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
	if (!validate_flag(map, "NO"))
		return (0);
	if (!validate_flag(map, "SO"))
		return (0);
	if (!validate_flag(map, "WE"))
		return (0);
	if (!validate_flag(map, "EA"))
		return (0);
	if (!validate_flag(map, "F"))
		return (0);
	if (!validate_flag(map, "C"))
		return (0);
	return (1);
}

//TODO:
// MLX does verify if the image exists
// But I want to do it on my own before we allocate more than needed.
static int	_validate_textures(char **map) 
{
	if (!ft_access(find_flag(map, "NO")))
		return (0);
	if (!ft_access(find_flag(map, "SO")))
		return (0);
	if (!ft_access(find_flag(map, "WE")))
		return (0);
	if (!ft_access(find_flag(map, "EA")))
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
	if (!ft_strmapiteri(map, find_player))
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

	if (!filename)
		return (cuberr(NO_ARGUMENT), NULL);
	if (!_validate_filename(filename))
		return (cuberr(INVALID_FILE), NULL);
	map = read_from_file(open(filename, O_RDONLY));
	if (!map)
		return (cuberr(INVALID_MAP), NULL);
	if (!_validate_flags(map))
		return (ft_free(map), cuberr(INVALID_FLAGS), NULL);
	if (!_validate_textures(map))
		return (ft_free(map), cuberr(INVALID_TEXTURE_FILES), NULL);
	//if (!_validate_map(&map[6])) TODO: Make a seperate map for validation.
	//	return (ft_free(map), cuberr(INVALID_MAP), NULL);
	return (map);
}
