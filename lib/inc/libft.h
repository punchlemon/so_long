/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:39:42 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:39:43 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

// item.c
typedef struct s_item
{
	void	*addr;
	void	*(*delete)(void *);
	int		(*print)(void *, int, int *);
}	t_item;
t_item	*create_item(void *addr, void *(*delete)(void *),
			int (*print)(void *, int, int *));
void	*delete(t_item *item);
int		print(t_item *item, int fd, int *res);

// common.c
size_t	ft_strlen(const char *s);
size_t	update_cap(size_t len, size_t *cap);
int		write_char_pointer(char *str, int fd, int *res);
void	ft_memcpy(char *dst, char *src, size_t n);
t_item	*update_string(t_item *str_item, int mode);

// string.c
typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	cap;
}	t_string;
t_item	*create_string(char *src);
void	*delete_string(void *s);
t_item	*append_string_src(t_item *str_item, char *src);
t_item	*append_string(t_item *str_item, t_item *src_item);
int		print_string(void *s, int fd, int *res);
int		print_string_only(void *s, int fd, int *res);

// array.c
typedef struct s_array
{
	void	**p;
	size_t	size;
	size_t	len;
	size_t	cap;
	void	*(*delete)(void *);
	int		(*print)(void *, int, int *);
}	t_array;
t_item	*create_array(size_t size, void *(*delete)(void *),
			int (*print)(void *, int, int *));
// void	*delete_array(void *);
// t_item	*append_array(t_item *, t_item *);
// int		print_array(void *, int, int *);

// list.c
typedef struct s_list
{
	t_item			*item;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;
t_item	*create_list(void);
void	*delete_list(void *sep);
t_item	*append_list(t_item *lines, t_item *item);
int		print_list(void *sep, int fd, int *res);
int		print_list_expand(void *sep, int fd, int *int_res);

// file.c
typedef struct s_file
{
	t_item	*path;
	t_item	*name;
	t_item	*lines;
	int		line_num;
	int		fd;
}	t_file;
t_item	*create_file(char *path, char *name);
void	*delete_file(void *f);
int		print_file(void *f, int fd, int *int_res);

#endif
