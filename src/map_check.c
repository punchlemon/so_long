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

void	width_chk(t_data * d, t_list *start, t_cordinate *map_size)
{
	t_list		*l;
	t_string	*s;
	size_t		i;

	l = start;
	s = (t_string *)(l->item->addr);
	map_size->x = s->len;
	if (map_size->x < 3)
		error(d, "The map width is too short.");
	i = 0;
	while (++i < map_size->y)
	{
		l = l->next;
		s = (t_string *)(l->item->addr);
		if (map_size->x != s->len)
			error(d, "The map is not rectangular.");
	}
}

void	surround_one_chk(t_data *d, t_list *start, t_cordinate *map_size)
{
	t_list		*l;
	t_string	*s;
	size_t		i;

	l = start;
	s = (t_string *)(l->item->addr);
	i = -1;
	while (++i < map_size->x)
		if (s->str[i] != '1')
			error(d, "The map is not surrounded by '1'.");
	i = 0;
	while (++i < map_size->y)
	{
		l = l->next;
		s = (t_string *)(l->item->addr);
		if (s->str[0] != '1' || s->str[s->len - 1] != '1')
			error(d, "The map is not surrounded by '1'.");
	}
	i = -1;
	while (++i < map_size->x)
		if (s->str[i] != '1')
			error(d, "The map is not surrounded by '1'.");
}

void	include_char_chk(t_data *d, t_list *l)
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
				error(d, "The map contains incorrect letter.");
		}
	}
	if (d->map_inf.c_cnt < 1)
		error(d, "The map doesn't contain 'C'.");
	if (d->map_inf.e_cnt != 1)
		error(d, "The map doesn't contain one 'E'.");
	if (d->map_inf.p_cnt != 1)
		error(d, "The map doesn't contain one 'P'.");
}

int	check_file(t_data *d)
{
	t_file		*f;
	t_list		*l;

	if (!d->ber)
		return (error(d, "The file can't open."));
	f = (t_file *)(d->ber->addr);
	if (!f->lines)
		return (error(d, "The file can't get line."));
	d->map_size.y = f->line_num;
	if (d->map_size.y < 3)
		return (error(d, "The map height is too short."));
	l = ((t_list *)(f->lines->addr))->next;
	width_chk(d, l, &d->map_size);
	surround_one_chk(d, l, &d->map_size);
	include_char_chk(d, l);
	set_map(d, l);
	flood_fill(d);
	return (0);
}
