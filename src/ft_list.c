#include "ft_lib.h"

t_item	*create_list(void)
{
	t_item	*res;
	t_list	*sep;

	sep = malloc(sizeof(t_list));
	if (!sep)
		return (NULL);
	res = malloc(sizeof(t_item));
	if (!res)
		return (free(sep), NULL);
	res->addr = sep;
	res->delete = delete_list;
	res->print = print_list;
	sep->item = NULL;
	sep->prev = sep;
	sep->next = sep;
	return (res);
}

void	*delete_list(t_item *item)
{
	t_list	*sep;
	t_list	*i;
	t_list	*tmp;

	if (!item)
		return (NULL);
	sep = (t_list *)item->addr;
	if (!sep)
		return (NULL);
	i = sep->next;
	while (i != sep)
	{
		tmp = i->next;
		delete_item(i->item);
		i = tmp;
	}
	free(i);
	return (NULL);
}

t_item	*append_list(t_item *list_item, t_item *item)
{
	t_list	*sep;
	t_list	*tmp;
	t_item	*new;
	t_list	*new_list;

	if (!list_item)
		return (NULL);
	sep = (t_list *)list_item->addr;
	new = create_list();
	if (!new)
		return (NULL);
	new_list = (t_list *)new->addr;
	if (!new_list)
		return (delete_item(list_item), delete_item(item), NULL);
	new_list->item = item;
	tmp = sep->prev->prev;
	tmp->next = new_list;
	new_list->prev = tmp;
	new_list->next = sep;
	sep->prev = new_list;
	return (list_item);
}

int	print_list(t_item *res, int fd, int *int_res)
{
	t_list	*i;
	t_list	*sep;

	sep = (t_list *)res->addr;
	if (!res || !sep)
		return (0);
	*int_res = 0;
	if (write_char_pointer("[", fd, int_res) == -1)
		return (-1);
	i = sep->next;
	while (i != sep)
	{
		if (print_item(i->item, fd, int_res) == -1)
			return (-1);
		i = i->next;
		if (i != sep && write_char_pointer(", ", fd, int_res) == -1)
			return (-1);
	}
	return (write_char_pointer("]\n", fd, int_res));
}

int	print_list_expand(t_item *res, int fd, int *int_res)
{
	t_list	*i;
	t_list	*sep;

	sep = (t_list *)res->addr;
	if (!sep)
		return (0);
	*int_res = 0;
	if (write_char_pointer("[\n", fd, int_res) == -1)
		return (-1);
	i = sep->next;
	while (i != sep)
	{
		if (write_char_pointer("\t", fd, int_res) == -1)
			return (-1);
		if (print_item(i->item, fd, int_res) == -1)
			return (-1);
		i = i->next;
		if (i != sep && write_char_pointer(",\n", fd, int_res) == -1)
			return (-1);
	}
	return (write_char_pointer("]\n", fd, int_res));
}
