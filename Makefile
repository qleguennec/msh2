NAME = minishell
SRC = $(filter %.c, $(shell ls))
OBJ = $(SRC:.c=.o)
LIB = libft/libft.a libvect/libvect.a libdict/libdict.a liblst/liblst.a

INCS +=
CFLAGS += -g -Wall -Wextra -Werror $(INCS)
LDLIBS += -llst -ldict -lvect -lft
LOADLIBES += -Llibft -Llibvect -Llibdict -Lliblst
LDFLAGS += -g

all: $(LIB) $(NAME)

$(NAME): $(OBJ)

%.a:
	make -C $(shell echo $*.a | sed 's/\// /')

clean:
	@rm $(OBJ) 2> /dev/null || true

fclean: clean
	@rm $(NAME) 2> /dev/null || true

re: fclean all

.PHONY: all clean fclean re
