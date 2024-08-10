/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:32:28 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:32:30 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	width_chk(t_list *start, t_cordinate *map_size)
{
	t_list		*l;
	t_string	*s;
	size_t		i;

	l = start;
	s = (t_string *)(l->item->addr);
	map_size->x = s->len;
	if (map_size->x < 3)
		return (1);
	i = 0;
	while (++i < map_size->y)
	{
		l = l->next;
		s = (t_string *)(l->item->addr);
		if (map_size->x != s->len)
			return (1);
	}
	return (0);
}

int	surround_one_chk(t_list *start, t_cordinate *map_size)
{
	t_list		*l;
	t_string	*s;
	size_t		i;

	l = start;
	s = (t_string *)(l->item->addr);
	i = -1;
	while (++i < map_size->x)
		if (s->str[i] != '1')
			return (1);
	i = 0;
	while (++i < map_size->y)
	{
		l = l->next;
		s = (t_string *)(l->item->addr);
		if (s->str[0] != '1' || s->str[s->len - 1] != '1')
			return (1);
	}
	i = -1;
	while (++i < map_size->x)
		if (s->str[i] != '1')
			return (1);
	return (0);
}

int	include_char_chk(t_list *l, t_data *d)
{
	t_cordinate	cord;
	char		c;

	l = l->prev;
	cord.x = -1;
	while (++cord.x < d->map_size.y)
	{
		l = l->next;
		cord.y = -1;
		while (++cord.y < d->map_size.x)
		{
			c = ((t_string *)(l->item->addr))->str[cord.y];
			d->map_inf.c_cnt += (c == 'C');
			d->map_inf.e_cnt += (c == 'E');
			d->map_inf.p_cnt += (c == 'P');
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
				return (1);
		}
	}
	if (d->map_inf.c_cnt < 1 || d->map_inf.e_cnt != 1 || d->map_inf.p_cnt != 1)
		return (1);
	return (0);
}

int	check_file(t_item *file, t_data *d)
{
	t_file		*f;
	t_list		*l;

	if (!file)
		return (1);
	f = (t_file *)(file->addr);
	if (!f->lines)
		return (1);
	d->map_size.y = f->line_num;
	if (d->map_size.y < 3)
		return (1);
	l = ((t_list *)(f->lines->addr))->next;
	if (width_chk(l, &d->map_size) || surround_one_chk(l, &d->map_size)
		|| include_char_chk(l, d))
		return (1);
	set_map(d, l);
	if (flood_fill(d))
		return (1);
	return (0);
}
