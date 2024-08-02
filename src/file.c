#include "ft_lib.h"
#include "get_next_line.h"
#include <fcntl.h>

void	*read_file(int fd, t_item *res)
{
	char	*tmp;
	t_item	*i;
	t_list	*l;

	if (!res || !res->addr)
		return (NULL);
	l = (t_list *)res->addr;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		i = create_string(tmp);
		if (!i)
			return (NULL);
		append_list(res, i);
	}
	close(fd);
	return (l);
}

t_item	*create_file(char *path, char *name)
{
	t_item	*res;
	t_file	*f;

	f = malloc(sizeof(t_file *));
	if (!f)
		return (NULL);
	res = malloc(sizeof(t_item));
	if (!res)
		return (free(f), NULL);
	res->addr = f;
	res->delete = delete_file;
	res->print = print_file;
	f->path = create_string(path);
	f->name = create_string(name);
	f->lines = create_list();
	f->fd = open(path, O_RDONLY);
	if (!f->path || !f->name || !f->lines || f->fd == -1)
		return (delete_item(res));
	if (!read_file(f->fd, f->lines))
		return (delete_item(res), NULL);
	return (res);
}

void	*delete_file(t_item *i)
{
	t_file	*f;

	if (!i)
		return (NULL);
	f = (t_file *)i->addr;
	if (!f)
		return (NULL);
	if (f->path)
		delete_string(f->path);
	if (f->name)
		delete_string(f->name);
	if (f->lines)
		delete_list(f->lines);
	return (free(f), NULL);
}

int	print_file(t_item *i, int fd, int *int_res)
{
	t_file	*f;
	int		tmp;

	f = (t_file *)i->addr;
	if (!f || !f->name || !f->lines)
		return (0);
	*int_res = print_string(f->name, fd, int_res);
	if (*int_res == -1)
		return (-1);
	if (write_char_pointer("\n================\n", fd, int_res) == -1)
		return (-1);
	tmp = print_list_expand(f->lines, fd, int_res);
	if (tmp == -1)
		return (-1);
	*int_res += tmp;
	if (write_char_pointer("\n================\n", fd, int_res) == -1)
		return (-1);
	return (*int_res);
}
