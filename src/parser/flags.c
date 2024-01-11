#include "cub3d.h"

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
			&& !ft_isempty(&arr[i][len]))
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
			&& !ft_isempty(&arr[i][len]))
			found++;
		i++;
	}
	if (!found)
		return (0);
	return (1);
}
