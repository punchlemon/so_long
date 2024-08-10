/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:02:25 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 16:02:26 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	*delete_list(void *sep)
{
	t_list	*i;
	t_list	*tmp;

	if (!sep)
		return (NULL);
	i = ((t_list *)sep)->next;
	while (i != sep)
	{
		tmp = i->next;
		delete(i->item);
		free(i);
		i = tmp;
	}
	free(i);
	return (NULL);
}

t_item	*append_list(t_item *lines, t_item *item)
{
	t_list	*sep;
	t_list	*tmp;
	t_list	*new;

	if (!lines)
		return (NULL);
	sep = (t_list *)lines->addr;
	new = malloc(sizeof(t_list));
	if (!new)
		return (delete(lines), delete(item), NULL);
	new->item = item;
	tmp = sep->prev;
	tmp->next = new;
	new->prev = tmp;
	new->next = sep;
	sep->prev = new;
	return (lines);
}

int	print_list(void *sep, int fd, int *res)
{
	t_list	*i;

	if (!sep)
		return (*res = -1, -1);
	if (write_char_pointer("[", fd, res) == -1)
		return (-1);
	i = ((t_list *)sep)->next;
	while (i != sep)
	{
		if (print(i->item, fd, res) == -1)
			return (-1);
		i = i->next;
		if (i != sep && write_char_pointer(", ", fd, res) == -1)
			return (-1);
	}
	return (write_char_pointer("]\n", fd, res));
}

int	print_list_expand(void *sep, int fd, int *int_res)
{
	t_list	*i;

	if (!sep)
		return (0);
	if (write_char_pointer("[\n", fd, int_res) == -1)
		return (-1);
	i = ((t_list *)sep)->next;
	while (i != sep)
	{
		if (write_char_pointer("\t", fd, int_res) == -1)
			return (-1);
		if (print(i->item, fd, int_res) == -1)
			return (-1);
		i = i->next;
		if (i != sep && write_char_pointer(",\n", fd, int_res) == -1)
			return (-1);
	}
	return (write_char_pointer("]\n", fd, int_res));
}
