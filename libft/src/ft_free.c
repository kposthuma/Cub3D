/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_free.c										  :+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2022/10/16 09:52:12 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/29 13:49:26 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **arg)
{
	size_t	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i])
			free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
	arg = NULL;
}

void	ft_free_size(char **arg, size_t size)
{
	size_t	i;

	i = 0;
	while (arg && i < size)
	{
		if (arg[i])
			free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
	arg = NULL;
}
