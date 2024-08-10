#include "libft.h"
#include <unistd.h>

t_item	*create_string(char *src)
{
	t_string	*s;
	t_item		*res;

	s = (t_string *)malloc(sizeof(t_string));
	if (!s)
		return (NULL);
	res = (t_item *)malloc(sizeof(t_item));
	if (!res)
		return (free(s), NULL);
	res->addr = s;
	res->delete = delete_string;
	res->print = print_string;
	s->len = ft_strlen(src);
	if (s->len == 0)
		return (s->str = NULL, s->cap = 0, res);
	s->cap = 1;
	s->str = src;
	update_cap(s->len, &s->cap);
	update_string(res, 0);
	return (res);
}

void	*delete_string(void *s)
{
	if (!s)
		return (NULL);
	if (((t_string *)s)->str)
		free(((t_string *)s)->str);
	free(s);
	return (NULL);
}

t_item	*append_string_src(t_item *str_item, char *src)
{
	t_string	*str;
	size_t		str_len;
	size_t		src_len;

	if (!str_item)
		return (NULL);
	str = (t_string *)str_item->addr;
	str_len = str->len;
	src_len = ft_strlen(src);
	if (src_len == 0)
		return (str_item);
	if (update_cap(str_len + src_len, &str->cap))
		update_string(str_item, 1);
	ft_memcpy(str->str + str_len, src, src_len);
	str->len += src_len;
	return (str_item);
}

t_item	*append_string(t_item *str_item, t_item *src_item)
{
	t_string	*str;
	t_string	*src;
	size_t		str_len;
	size_t		src_len;

	str = (t_string *)str_item->addr;
	src = (t_string *)src_item->addr;
	str_len = str->len;
	src_len = src->len;
	if (src_len == 0)
		return (str_item);
	if (update_cap(str_len + src_len, &str->cap))
		update_string(str_item, 1);
	ft_memcpy(str->str + str_len, src->str, src_len);
	str->len += src_len;
	return (delete(src_item), str_item);
}

int	print_string(void *s, int fd, int *res)
{
	int			tmp;

	if (!res || !s)
		return (0);
	if (!s)
		return (0);
	if (!((t_string *)s)->str)
		return (0);
	tmp = write(fd, ((t_string *)s)->str, ((t_string *)s)->len);
	if (tmp == -1)
		return (*res = -1, -1);
	*res += tmp;
	tmp = write(fd, "\n", 1);
	if (tmp == -1)
		return (*res = -1, -1);
	*res += tmp;
	return (*res);
}

int	print_string_only(void *s, int fd, int *res)
{
	int			tmp;

	if (!res || !s)
		return (0);
	if (!s)
		return (0);
	if (!((t_string *)s)->str)
		return (0);
	tmp = write(fd, ((t_string *)s)->str, ((t_string *)s)->len);
	if (tmp == -1)
		return (*res = -1, -1);
	*res += tmp;
	return (*res);
}
