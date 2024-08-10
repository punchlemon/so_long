/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:57:11 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:57:12 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
