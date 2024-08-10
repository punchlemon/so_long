/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:50:01 by retanaka          #+#    #+#             */
/*   Updated: 2024/07/18 16:50:03 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error(t_data *d, char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	close_mlx(d);
	exit(1);
	return (1);
}

int	close_mlx(t_data *d)
{
	size_t	i;

	i = -1;
	while (++i < 5)
		delete(d->tiles[i]);
	i = -1;
	if (d->map)
	{
		while (++i < d->map_size.y)
			if (d->map[i])
				free(d->map[i]);
		free(d->map);
	}
	free(d->tiles);
	mlx_loop_end(d->mlx);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	return (0);
}

int	key_event(int key, t_data *d)
{
	if (key == ESC)
		return (close_mlx(d), exit(0), 0);
	return (0);
}
