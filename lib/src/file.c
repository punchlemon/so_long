#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>

int	print_file_contents(void *lines, int fd, int *res);

void	*read_file(int fd, t_item *lines, int *line_num)
{
	char	*tmp;
	t_item	*str;
	t_list	*sep;

	if (!lines || !lines->addr)
		return (NULL);
	*line_num = 0;
	sep = (t_list *)(lines->addr);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		str = create_string(tmp);
		free(tmp);
		if (!str)
			return (NULL);
		str->print = print_string_only;
		append_list(lines, str);
		(*line_num)++;
	}
	close(fd);
	return (sep);
}

t_item	*create_file(char *path, char *name)
{
	t_item	*res;
	t_file	*f;

	f = (t_file *)malloc(sizeof(t_file));
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
		return (delete(res));
	f->path->print = print_string_only;
	f->name->print = print_string_only;
	if (!read_file(f->fd, f->lines, &f->line_num))
		return (delete(res), NULL);
	return (res);
}

void	*delete_file(void *f)
{
	if (!f)
		return (NULL);
	if (((t_file *)f)->path)
		delete(((t_file *)f)->path);
	if (((t_file *)f)->name)
		delete(((t_file *)f)->name);
	if (((t_file *)f)->lines)
		delete(((t_file *)f)->lines);
	return (free((t_file *)f), NULL);
}

int	print_file_title(void *f, int fd, int *int_res)
{
	char	*p;

	if (!f || !((t_file *)f)->name || !((t_file *)f)->path)
		return (0);
	p = "File name : [";
	if (write_char_pointer(p, fd, int_res) == -1)
		return (-1);
	if (print(((t_file *)f)->name, fd, int_res) == -1)
		return (-1);
	p = "]\nPath      : [";
	if (write_char_pointer(p, fd, int_res) == -1)
		return (-1);
	if (print(((t_file *)f)->path, fd, int_res) == -1)
		return (-1);
	p = "]";
	if (write_char_pointer(p, fd, int_res) == -1)
		return (-1);
	return (*int_res);
}

int	print_file_contents(void *lines, int fd, int *res)
{
	t_list		*i;

	if (!lines)
		return (*res = -1, -1);
	i = ((t_list *)lines)->next;
	while (i != lines)
	{
		if (print(i->item, fd, res) == -1)
			return (-1);
		i = i->next;
	}
	return (*res);
}

int	print_file(void *f, int fd, int *int_res)
{
	char	*p;

	if (!f || !((t_file *)f)->lines)
		return (0);
	if (print_file_title(f, fd, int_res) == -1)
		return (-1);
	p = "\n================================================================\n";
	if (write_char_pointer(p, fd, int_res) == -1)
		return (-1);
	if (print_file_contents(((t_file *)f)->lines->addr, fd, int_res) == -1)
		return (-1);
	if (write_char_pointer(p, fd, int_res) == -1)
		return (-1);
	return (*int_res);
}

t_string	*get_line(void *f, int n)
{
	t_list	*s;

	if (!f || !((t_file *)f)->lines || n >= ((t_file *)f)->line_num)
		return (NULL);
	s = ((t_list *)(((t_file *)f)->lines->addr))->next;
	while (--n)
		s = s->next;
	return ((t_string *)s->item->addr);
}
