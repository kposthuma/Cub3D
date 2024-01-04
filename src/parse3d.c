/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse3d.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 17:07:48 by kposthum      #+#    #+#                 */
/*   Updated: 2024/01/04 18:41:38 by kposthum      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_filetype(char *file, char *type)
{
	size_t	t_len;
	size_t	f_len;

	f_len = ft_strlen(file);
	t_len = ft_strlen(type);
	if (t_len >= f_len)
		return (false);
	while (t_len > 0)
	{
		if (file[f_len -1] != type[t_len - 1])
			return (false);
		f_len--;
		t_len--;
	}
	return (true);
}

t_data	**head_init(int fd)
{
	char	*line;
	t_data	**head;
	t_data	*node;

	head = ft_calloc(1, sizeof(t_data *));
	if (head == NULL)
		return (errmsg("Memory error."), NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		node = newnode((void *)line);
		if (node == NULL)
			return (errmsg("Memory error."), clear_list_pre(head), NULL);
		add_node(head, node);
		line = get_next_line(fd);
	}
	return (head);
}

void	clear_empty_line(t_data **head)
{
	t_data	*node;
	t_data	*temp;

	node = *head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (temp->flag == TO_CLEAR)
			clear_node(head, temp);
	}
}

t_data	**parse_file(int fd)
{
	t_data	**head;

	head = head_init(fd);
	if (!head || !(*head))
		return (free(head), NULL);
	if ((*head)->cont == NULL)
		return (errmsg("Empty file."), free(head), NULL);
	assign_flag(head);
	clear_empty_line(head);
	if (!count_flag(head))
		return (errmsg("incorrect number of elements"),
			clear_list_pre(head), NULL);
	if (!validate_map(head))
		return (errmsg("invalid map"), clear_list_pre(head), NULL);
	if (!(validate_color(head, C_COLOR) && validate_color(head, F_COLOR)))
		return (errmsg("invalid color value"), clear_list_two(head), NULL);
	if (!(validate_texture(head, N_TEXTURE) && validate_texture(head, E_TEXTURE)
			&& validate_texture(head, S_TEXTURE)
			&& validate_texture(head, W_TEXTURE)))
		return (errmsg("invalid texture path"), clear_list_t(head), NULL);
	return (head);
}

t_data	**parse_input(int count, char **arg)
{
	int		fd;
	t_data	**head;

	if (count != 2)
		return (errmsg("No mapfile provided."), NULL);
	if (!check_filetype((arg[1]), ".cub"))
		return (errmsg("Incorrect filetype provided."), NULL);
	fd = open(arg[1], O_RDONLY);
	if (fd < 0)
		return (errmsg("Unable to open file."), NULL);
	head = parse_file(fd);
	close(fd);
	return (head);
}
