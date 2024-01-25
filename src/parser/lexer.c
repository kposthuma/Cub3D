/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 11:36:39 by cbijman       #+#    #+#                 */
/*   Updated: 2024/01/25 16:47:39 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if a given string represents a valid map line.
 *
 * @param str The string to be checked.
 * @return True if the string is a valid map line, false otherwise.
 */
static bool	_is_map_line(char *str)
{
	static bool	started = false;
	size_t		i;

	if (!str)
		return (false);
	i = 0;
	if (!started && ft_isempty(str))
		return (false);
	while (str[i])
	{
		if (!ft_isspace(str[i])
			&& str[i] != '1'
			&& str[i] != '0'
			&& !ft_strchr("NEWS", str[i])
			&& !ft_strchr("NEWS", str[i + 1]))
			return (false);
		i++;
	}
	started = true;
	return (true);
}

/**
 * Adds a flag to the linked list of data nodes.
 * 
 * @param head The head of the linked list.
 * @param str The string representing the flag to be added.
 * @return Returns true if the flag was successfully added, false otherwise.
 */
static bool	_add_flag(t_data **head, char *str)
{
	t_data	*nnode;

	if (find_node(head, MAP))
		return (free(str), false);
	if (ft_isempty(str))
		return (free(str), true);
	nnode = new_node(ft_trim_whitespace(str), FLAG);
	if (!nnode)
		return (free(str), false);
	add_node(head, nnode);
	return (true);
}

/**
 * Adds a map node to the linked list.
 *
 * @param head The head of the linked list.
 * @param str The string representing the map.
 * @return True if the map node was successfully added, false otherwise.
 */
static bool	_add_map(t_data **head, char *str)
{
	t_data	*nnode;

	nnode = new_node(str, MAP);
	if (!nnode)
		return (free(str), false);
	add_node(head, nnode);
	return (true);
}

/**
 * Reads the map from a file descriptor and stores it in a linked list structure.
 *
 * @param fd The file descriptor of the map file.
 * @return A pointer to the linked list structure containing the map data,
 *  or NULL *  if an error occurs.
 */
t_data	*read_map_to_struct(int fd)
{
	t_data	*list;
	char	*str;

	list = NULL;
	str = "\0";
	while (str)
	{
		str = get_next_line(fd);
		if (!str)
			continue ;
		ft_trimnl(str);
		if (_is_map_line(str))
		{
			if (!_add_map(&list, str))
				return (free(str), clear_nodes(&list), NULL);
		}
		else if (!_add_flag(&list, str))
			return (free(str), clear_nodes(&list), NULL);
	}
	return (list);
}
