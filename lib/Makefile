NAME				=	libft.a
INC_DIR				=	inc
SRC_DIR				=	src
OBJ_DIR				=	obj

FILES				=	 \
						common \
						file \
						get_next_line \
						item \
						list \
						string \

CC					=	gcc
AR					=	ar
CFLAGS				=	-Wall -Werror -Wextra
ARFLAGS				=	rcs
IFLAGS				=	-I$(INC_DIR)

OBJ_EXIST			=	.obj

SRCS				=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(FILES)))
OBJS				=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c | $(OBJ_EXIST)
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_EXIST):
						@mkdir -p $(OBJ_DIR)

all:					$(NAME)

$(NAME):				$(OBJS)
						@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
						@$(RM) -rf $(OBJ_DIR)
						@$(RM) $(NAME)

re:						clean all

.PHONY:					all clean re