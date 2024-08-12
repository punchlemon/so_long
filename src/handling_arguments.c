/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:14:05 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 19:14:05 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strcmpare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (1);
	return (0);
}

char	*join_str(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = malloc(s1_len + s2_len + 1);
	if (!res)
		return (NULL);
	res[s1_len + s2_len] = '\0';
	while (s2_len--)
		res[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		res[s1_len] = s1[s1_len];
	return (res);
}

int	handling_arguments(t_data *d, int argc, char **argv)
{
	size_t	str_len;
	char	*path;

	if (argc != 2)
		return (error(d, "The number of arguments is different."));
	str_len = ft_strlen(argv[1]);
	if (str_len < 5 || ft_strcmpare(argv[1] + str_len - 4, ".ber"))
		return (error(d, "File name is not valid."));
	path = join_str("maps/", argv[1]);
	if (!path)
		return (error(d, "Can't allocate space."));
	d->ber = create_file(path, argv[1]);
	free(path);
	if (!d->ber)
		return (error(d, "Can't open file."));
	return (0);
}
