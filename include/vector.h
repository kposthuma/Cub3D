/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 14:08:27 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/17 14:08:28 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct e_vector
{
	char	**content;
	int		index;
	int		type_size;
	int		length;
}			t_vector;

#endif