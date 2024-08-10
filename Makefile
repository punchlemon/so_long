NAME				=	so_long
LIB					=	ft
INC_DIR				=	inc
SRC_DIR				=	src
OBJ_DIR				=	obj
LIB_DIR				=	lib

FILES				=	 \
						main \
						event_handler \
						tile \

CC					=	gcc
XFLAGS				=	-Lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -O3
CFLAGS				=	-Wall -Werror -Wextra -g
IFLAGS				=	-I$(INC_DIR) -Imlx -I/usr/include -I$(LIB_DIR)/$(INC_DIR)
LFLAGS				=	-L$(LIB_DIR) -l$(LIB)
VFLAGS				=	 \
						--track-origins=yes \
						--leak-check=full \
						# --show-leak-kinds=all \
						-s \

LOGFILE				=	valgrind_result.log

OBJ_EXIST			=	.obj

SRCS				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJS				=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c | $(OBJ_EXIST)
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_EXIST):
						@mkdir -p $(OBJ_DIR)

all:					$(NAME)

val:					re
						@valgrind $(VFLAGS) ./$(NAME) > $(LOGFILE) 2>&1

$(NAME):				$(OBJS)
						@make all --no-print-directory -C $(LIB_DIR)
						@$(CC) $(OBJS) $(LFLAGS) $(XFLAGS) -o $(NAME)

lib_clean:
						@make clean --no-print-directory -C $(LIB_DIR)

clean:					lib_clean
						@$(RM) -rf $(OBJ_DIR)

fclean:					clean
						@$(RM) $(NAME)
						@$(RM) $(LOGFILE)

re:						fclean all

.PHONY:					all clean fclean re