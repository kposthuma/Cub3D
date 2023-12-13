/* ************************************************************************** */
/*																			*/
/*														::::::::			*/
/*   ft_isprint.c									   :+:	:+:			*/
/*													 +:+					*/
/*   By: kposthum <kposthum@student.codam.nl>		 +#+					 */
/*												   +#+					  */
/*   Created: 2022/10/04 12:59:35 by kposthum	  #+#	#+#				 */
/*   Updated: 2023/08/29 13:49:26 by kposthum	  ########   odam.nl		 */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
