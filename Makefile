NAME								=	so_long
INC_DIR								=	inc
SRC_DIR								=	src
OBJ_DIR								=	obj

FILES								=	 \
										event_handler \
										file \
										ft_common \
										ft_item \
										ft_list \
										ft_string \
										get_next_line \
										main \
										# tile \

CC									=	gcc
XFLAGS								=	-Lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -ljpeg -O3
CFLAGS								=	-Wall -Werror -Wextra -g
IFLAGS								=	-I$(INC_DIR) -Imlx -I/usr/include

OBJ_EXIST							=	.obj

SRCS								=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJS								=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

$(OBJ_DIR)/%.o:							$(SRC_DIR)/%.c | $(OBJ_EXIST)
										@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_EXIST):
										@mkdir -p $(OBJ_DIR)

val:									re
										@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) > valgrind_result.log 2>&1

all:									$(NAME)

$(NAME):								$(OBJS)
										@$(CC) $(OBJS) $(CFLAGS) $(IFLAGS) $(XFLAGS) -o $(NAME)

clean:
										@$(RM) -rf $(OBJ_DIR)

fclean:									clean
										@$(RM) $(NAME)

re:										fclean all

.PHONY:									all clean fclean re