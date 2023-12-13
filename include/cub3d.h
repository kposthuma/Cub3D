/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 16:58:52 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/13 14:52:37 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <math.h>
# include <stdbool.h>

# ifndef ALLOWED
#  define ALLOWED "10 NESW"
# endif

typedef enum e_flag
{
	C_COLOR = 0,
	F_COLOR = 1,
	N_TEXTURE = 2,
	E_TEXTURE = 3,
	S_TEXTURE = 4,
	W_TEXTURE = 5,
	MAP_START = 6,
	TO_CLEAR = 7,
}	t_flag;

typedef struct s_data
{
	int				flag;
	void			*cont;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;
// err3d.c
void	errmsg(char *msg);
// parse3d.c
t_data	**parse_input(int count, char **arg);
// list3d.c
void	clear_list_pre(t_data **head);
t_data	*newnode(void *cont);
void	clear_node(t_data **head, t_data *node);
void	add_node(t_data **head, t_data *node);
// map3d.c
bool	validate_map(t_data **head);
#endif
