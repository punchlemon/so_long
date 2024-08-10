#ifndef FT_LIB_H
# define FT_LIB_H

# include <stdlib.h>

// item.c
typedef struct s_item {
	void	*addr;
	void	*(*delete)(void *);
	int		(*print)(void *, int, int *);
}	t_item;
t_item	*create_item(void *, void *(*delete)(void *), int (*print)(void *, int, int *));
void	*delete(t_item *);
int		print(t_item *, int, int *);

// common.c
size_t	ft_strlen(const char *);
size_t	update_cap(size_t, size_t *);
int		write_char_pointer(char *, int, int *);
void	ft_memcpy(char *, char *, size_t);
t_item	*update_string(t_item *, int);

// string.c
typedef struct s_string {
	char	*str;
	size_t	len;
	size_t	cap;
}	t_string;
t_item	*create_string(char *);
void	*delete_string(void *);
t_item	*append_string_src(t_item *, char *);
t_item	*append_string(t_item *, t_item *);
int		print_string(void *, int, int *);
int		print_string_only(void *, int, int *);

// array.c
typedef struct s_array {
	void	**p;
	size_t	size;
	size_t	len;
	size_t	cap;
	void	*(*delete)(void *);
	int		(*print)(void *, int, int *);
}	t_array;
t_item	*create_array(size_t, void *(*delete)(void *),
	int (*print)(void *, int, int *));
// void	*delete_array(void *);
// t_item	*append_array(t_item *, t_item *);
// int		print_array(void *, int, int *);

// list.c
typedef struct s_list {
	t_item			*item;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;
t_item	*create_list(void);
void	*delete_list(void *);
t_item	*append_list(t_item *, t_item *);
int		print_list(void *, int, int *);
int		print_list_expand(void *, int, int *);

// file.c
typedef struct s_file {
	t_item	*path;
	t_item	*name;
	t_item	*lines;
	int		line_num;
	int		fd;
}	t_file;
t_item	*create_file(char *, char *);
void	*delete_file(void *);
int		print_file(void *, int, int *);

#endif