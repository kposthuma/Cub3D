/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse3d.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kposthum <kposthum@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 17:07:48 by kposthum      #+#    #+#                 */
/*   Updated: 2023/12/17 16:33:48 by koen          ########   odam.nl         */
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
	line = get_next_line(fd);
	while (line != NULL)
	{
		node = newnode((void *)line);
		add_node(head, node);
		line = get_next_line(fd);
	}
	return (head);
}

void	assign_flag(t_data **head)
{
	t_data	*temp;
	char	*str;

	temp = *head;
	while (temp != NULL && (temp->prev == NULL
			|| temp->prev->flag != MAP_START))
	{
		str = (char *)temp->cont;
		while (*str && ft_isspace(*str) == 1)
			str++;
		if (*str == '\0' || ft_strlen(str) < 5)
			temp->flag = TO_CLEAR;
		else if (ft_strncmp(str, "NO ", 3) == 0)
			temp->flag = N_TEXTURE;
		else if (ft_strncmp(str, "SO ", 3) == 0)
			temp->flag = S_TEXTURE;
		else if (ft_strncmp(str, "EA ", 3) == 0)
			temp->flag = E_TEXTURE;
		else if (ft_strncmp(str, "WE ", 3) == 0)
			temp->flag = W_TEXTURE;
		else if (ft_strncmp(str, "F ", 2) == 0)
			temp->flag = F_COLOR;
		else if (ft_strncmp(str, "C ", 2) == 0)
			temp->flag = C_COLOR;
		else
			temp->flag = MAP_START;
		temp = temp->next;
	}
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

bool	count_flag(t_data **head)
{
	int		i;
	size_t	check;
	t_data	*node;

	i = C_COLOR;
	while (i <= MAP_START)
	{
		node = *head;
		check = 0;
		while (node != NULL && (node->prev == NULL
				|| node->prev->flag != MAP_START))
		{
			if (node->flag == i)
				check++;
			node = node->next;
		}
		if (check != 1)
			return (false);
		i++;
	}
	return (true);
}

t_data	**parse_file(int fd)
{
	t_data	**head;

	head = head_init(fd);
	if ((*head)->cont == NULL)
		return (errmsg("Empty file."), free(head), NULL);
	assign_flag(head);
	clear_empty_line(head);
	if (!count_flag(head))
		return (errmsg("incorrect number of elements"),
			clear_list_pre(head), NULL);
	if (!validate_map(head))
		return (errmsg("invalid map"), clear_list_pre(head), NULL);
	
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
