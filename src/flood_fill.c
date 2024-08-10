/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:31:56 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:31:57 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	flood_fill_rec(t_cordinate map_size, int **map, size_t y, size_t x)
{
	int	tmp;

	if (map[y][x] == 1 || map[y][x] >= 10)
		return (0);
	if (map[y][x] == E)
		return (1);
	if (map[y][x] < 10)
		map[y][x] += 10;
	tmp = 0;
	if (x > 1)
		tmp |= flood_fill_rec(map_size, map, y, x - 1);
	if (x < map_size.x - 2)
		tmp |= flood_fill_rec(map_size, map, y, x + 1);
	if (y > 1)
		tmp |= flood_fill_rec(map_size, map, y - 1, x);
	if (y < map_size.y - 2)
		tmp |= flood_fill_rec(map_size, map, y + 1, x);
	return (tmp);
}

void	get_cordinate(t_data *d, t_cordinate *cord, int i)
{
	cord->y = 0;
	while (cord->y < d->map_size.y)
	{
		cord->x = 0;
		while (cord->x < d->map_size.x)
		{
			if (d->map[cord->y][cord->x] == i)
				return ;
			cord->x++;
		}
		cord->y++;
	}
}

void	flood_fill(t_data *d)
{
	t_cordinate	cord;

	get_cordinate(d, &cord, P);
	if (!flood_fill_rec(d->map_size, d->map, cord.y, cord.x))
		error(d, "No path to the goal.");
	cord.y = -1;
	while (++cord.y < d->map_size.y)
	{
		cord.x = -1;
		while (++cord.x < d->map_size.x)
		{
			if (d->map[cord.y][cord.x] >= 10)
				d->map[cord.y][cord.x] -= 10;
		}
	}
}
