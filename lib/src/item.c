/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:01:33 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 16:01:33 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_item	*create_item(void *addr, void *(*delete)(void *),
			int (*print)(void *, int, int *))
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

void	*delete(t_item *item)
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

int	print(t_item *item, int fd, int *res)
{
	char	*c;

	if (!item)
		c = "item=NULL";
	else if (!(item->print))
		c = "item->print=NULL";
	else
		return (item->print(item->addr, fd, res));
	return (write_char_pointer(c, fd, res));
}
