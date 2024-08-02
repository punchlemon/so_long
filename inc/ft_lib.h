#ifndef FT_LIB_H
# define FT_LIB_H

# include <stdlib.h>

// ft_item.c
typedef struct s_item {
	void	*addr;
	void	*(*delete)(struct s_item *);
	int		(*print)(struct s_item *, int, int *);
}	t_item;
t_item	*create_item(void *, void *(*delete)(t_item *), int (*print)(t_item *, int, int *));
void	*delete_item(t_item *);
int		print_item(t_item *, int, int *);

// ft_common.c
size_t	ft_strlen(const char *);
size_t	update_cap(size_t, size_t *);
int		write_char_pointer(char *, int, int *);
void	ft_memcpy(char *, char *, size_t);
t_item	*update_string(t_item *, int);

// ft_string.c
typedef struct s_string {
	char	*str;
	size_t	len;
	size_t	cap;
}	t_string;
t_item	*create_string(char *);
void	*delete_string(t_item *);
t_item	*append_string_src(t_item *, char *);
t_item	*append_string(t_item *, t_item *);
int		print_string(t_item *, int, int *);

// ft_list.c
typedef struct s_list {
	t_item			*item;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;
t_item	*create_list(void);
void	*delete_list(t_item *);
t_item	*append_list(t_item *, t_item *);
int		print_list(t_item *, int, int *);
int		print_list_expand(t_item *, int, int *);

// file.c
typedef struct s_file {
	t_item	*path;
	t_item	*name;
	int			fd;
	t_item	*lines;
}	t_file;
t_item	*create_file(char *, char *);
void	*delete_file(t_item *);
int		print_file(t_item *, int, int *);

#endif