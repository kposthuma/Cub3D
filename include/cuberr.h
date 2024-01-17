/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cuberr.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 14:08:20 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/17 14:08:21 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBERR_H
# define CUBERR_H

# define ERR_NO_ARGUMENT "Invalid/No argument"
# define ERR_INVALID_FILE "Invalid file/permissions"
# define ERR_INVALID_MAP "Invalid map"
# define ERR_INVALID_FLAGS "Invalid flags or not every necessary flag defined"
# define ERR_WEIRD_FLAGS "Invalid flag found"
# define ERR_INVALID_TEXTURES "textures are not found or cannot be loaded"
# define ERR_NO_ERROR "No Error just not working..."

// Custom Error types for parsing and rendering, SpareRib Express is a defaulty
// Which prints "No Error just not working..."
typedef enum e_errortype
{
	NO_ARGUMENT = 1,
	INVALID_FILE,
	INVALID_MAP,
	INVALID_FLAGS,
	WEIRD_FLAGS,
	INVALID_TEXTURE_FILES,
	SPARERIB_EXPRESS
}	t_cuberror_type;

void	cuberr(t_cuberror_type type);

#endif