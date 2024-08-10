/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 16:00:29 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 16:00:30 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
