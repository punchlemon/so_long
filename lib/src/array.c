#include "libft.h"

t_item	*create_array(size_t size, void *(*delete)(void *),
	int (*print)(void *, int, int *))
{
	t_item	*res;
	t_array	*a;

	res = malloc(sizeof(t_item));
	if (!res)
		return (NULL);
	a = malloc(sizeof(t_array));
	if (!a)
		return (free(res), NULL);
	// res->print = print_array;
	// res->delete = delete_array;
	res->addr = a;
	a->p = NULL;
	a->delete = delete;
	a->print = print;
	a->size = size;
	a->len = 0;
	a->cap = 0;
	return (res);
}

// void	*delete_array(void *)
// {
// 	t_array
// }
