#include "ft_lib.h"

t_item	*create_item(void *addr, void *(*delete)(t_item *), int (*print)(t_item *, int, int *))
{
	t_item	*res;

	if (!addr || !delete || !print)
		return (NULL);
	res = malloc(sizeof(t_item));
	if (!res)
		return (NULL);
	res->addr = addr;
	res->delete = delete;
	res->print = print;
	return (res);
}

void	*delete_item(t_item *item)
{
	t_item	*res;
	t_item	*i;

	i = (t_item *)item;
	if (!i || !i->delete)
		return (NULL);
	res = i->delete(i->addr);
	free(i);
	return (res);
}

int	print_item(t_item *item, int fd, int *res)
{
	char	*c;

	if (!item)
		c = "item=NULL";
	else if (!item->print)
		c = "item->print=NULL";
	else
		return (item->print(item->addr, fd, res));
	return (write_char_pointer(c, fd, res));
}
