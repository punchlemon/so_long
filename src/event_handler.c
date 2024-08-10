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

int	close_mlx(t_data *d)
{
	int	i;

	i = -1;
	while (++i < 5)
		delete(d->tiles[i]);
	free(d->tiles);
	mlx_loop_end(d->mlx);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	exit(0);
	return (0);
}

int	key_event(int key, t_data *d)
{
	if (key == ESC)
		close_mlx(d);
	return (0);
}
