#include "cuberr.h"
#include "libft.h"
#include <unistd.h>

static void	invalid_map_parsing(t_cuberror_type type)
{
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
}

void	cuberr(t_cuberror_type type)
{
	if (type > 0)
		ft_putstr_fd("Error: ", 2);
	if (type > 0 && type < 5)
		invalid_map_parsing(type);
	if (type == SPARERIB_EXPRESS)
		ft_putendl_fd(ERR_NO_ERROR, STDERR_FILENO);
}

void	errmsg(char *msg)
{
	// Do Nothing
}
