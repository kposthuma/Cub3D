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