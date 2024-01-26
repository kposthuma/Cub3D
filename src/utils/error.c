/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 11:03:31 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/26 12:50:31 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cuberr.h"
#include "libft.h"
#include <unistd.h>

void	cuberr(t_cuberror_type type)
{
	if (type > 0)
		ft_putstr_fd("Error: ", 2);
	if (type == NO_ARGUMENT)
		ft_putendl_fd(ERR_NO_ARGUMENT, STDERR_FILENO);
	if (type == INVALID_FILE)
		ft_putendl_fd(ERR_INVALID_FILE, STDERR_FILENO);
	if (type == INVALID_MAP)
		ft_putendl_fd(ERR_INVALID_MAP, STDERR_FILENO);
	if (type == INVALID_FLAGS)
		ft_putendl_fd(ERR_INVALID_FLAGS, STDERR_FILENO);
	if (type == WEIRD_FLAGS)
		ft_putendl_fd(ERR_WEIRD_FLAGS, STDERR_FILENO);
	if (type == INVALID_TEXTURE_FILES)
		ft_putendl_fd(ERR_INVALID_TEXTURES, STDERR_FILENO);
	if (type == INVALID_COLOR)
		ft_putendl_fd(ERR_INVALID_COLOR, STDERR_FILENO);
	if (type == NOT_ENOUGH_MEMORY)
		ft_putendl_fd(ERR_NO_MEMORY, STDERR_FILENO);
	if (type == SPARERIB_EXPRESS)
		ft_putendl_fd(ERR_NO_ERROR, STDERR_FILENO);
}
