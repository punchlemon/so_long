/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:32:08 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:32:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	disp_map(t_data *d)
{
	t_cordinate	cord;
	int			i;
	t_tile		*t;

	cord.y = -1;
	while (++cord.y < d->map_size.y)
	{
		cord.x = -1;
		while (++cord.x < d->map_size.x)
		{
			i = d->map[cord.y][cord.x];
			t = ((t_tile *)d->tiles[i]->addr);
			mlx_put_image_to_window(d->mlx, d->win, t->img,
				cord.x * t->width, cord.y * t->height);
		}
	}
}

int	get_num(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (1);
	if (c == 'C')
		return (C);
	if (c == 'E')
		return (E);
	if (c == 'P')
		return (P);
	else
		return (0);
}

void	set_map(t_data *d, t_list *start)
{
	t_cordinate	cord;
	t_list		*l;
	char		c;

	l = start->prev;
	d->map = malloc(sizeof(int *) * d->map_size.y);
	if (!d->map)
		close_mlx(d);
	cord.y = -1;
	while (++cord.y < d->map_size.y)
	{
		l = l->next;
		d->map[cord.y] = malloc(sizeof(int) * d->map_size.x);
		if (!d->map[cord.y])
			close_mlx(d);
		cord.x = -1;
		while (++cord.x < d->map_size.x)
		{
			c = ((t_string *)(l->item->addr))->str[cord.x];
			d->map[cord.y][cord.x] = get_num(c);
		}
	}
}

void	update_map(t_data *d, int key)
{
	t_cordinate	cord;
	t_cordinate	c;

	get_cordinate(d, &cord, P);
	c.y = 0;
	c.x = 0;
	if (key == UP || key == UP_W)
		c.y = -1;
	else if (key == DOWN || key == DOWN_S)
		c.y = 1;
	else if (key == LEFT || key == LEFT_A)
		c.x = -1;
	else if (key == RIGHT || key == RIGHT_D)
		c.x = 1;
	if (d->map[cord.y + c.y][cord.x + c.x] == 1)
		return ;
	d->player_move++;
	if (d->map[cord.y + c.y][cord.x + c.x] == C)
		d->get_coin++;
	status(d);
	if (d->map[cord.y + c.y][cord.x + c.x] == E)
		success(d);
	d->map[cord.y][cord.x] = 0;
	d->map[cord.y + c.y][cord.x + c.x] = P;
	disp_map(d);
}
