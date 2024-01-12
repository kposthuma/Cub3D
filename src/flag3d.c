#include "cub3d.h"

static void	_assign_flag(t_data *temp, char *str)
{
	printf("_assign_flag called\n");
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
		_assign_flag(temp, str);
		temp = temp->next;
	}
}

void	set_flag_rest(t_data *node)
{
	//Do Nothing
	printf("set_flag_rest called\n");
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
