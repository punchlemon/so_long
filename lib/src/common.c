#include "libft.h"
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	update_cap(size_t len, size_t *cap)
{
	if (*cap >= len)
		return (0);
	while (1)
	{
		if (*cap < 1024)
			*cap *= 2;
		else
			*cap *= 1.25;
		if (*cap >= len)
			return (1);
	}
}

int	write_char_pointer(char *str, int fd, int *res)
{
	int	tmp;

	tmp = write(fd, str, ft_strlen(str));
	if (tmp == -1)
		return (*res = -1, -1);
	return (*res += tmp, *res);
}

void	ft_memcpy(char *dst, char *src, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		dst[i] = src[i];
}

t_item	*update_string(t_item *str_item, int mode)
{
	t_string	*str;
	char		*tmp;

	if (!str_item)
		return (NULL);
	str = (t_string *)str_item->addr;
	tmp = str->str;
	str->str = malloc(sizeof(char) * str->cap);
	if (!str->str)
		return (delete(str_item));
	ft_memcpy(str->str, tmp, str->len);
	if (mode == 1)
		free(tmp);
	return (str_item);
}

// cap should not be NULL
