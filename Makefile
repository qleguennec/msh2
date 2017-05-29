NAME = minishelL
SRC = bi_cd.c bi_echo.c bi_env.c bi_exit.c bi_setenv.c bi_unsetenv.c env_cpy_val.c expand_input.c fork_exec.c inp_query.c malloc_err.c minishell.c query_path.c
OBJ = $(SRC:.c=.o)
A = libft/libft.a libvect/libvect.a libdict/libdict.a libfmt/libfmt.a liblst/liblst.a
SUBDIRS = libft libvect libdict libfmt liblst

INCS +=
CFLAGS += -g -Wall -Wextra -Werror $(INCS)
LDLIBS += -llst -ldict -lfmt -lvect -lft
LOADLIBES += -Llibft -Llibvect -Llibdict -Lliblst -Llibfmt
LDFLAGS += -g

all: $(A) $(NAME)

$(NAME): $(OBJ)

%.a:
	make -C $(shell echo $*.a | sed 's/\// /')

clean: c
	@$(foreach dir, $(SUBDIRS), make -C $(dir) clean &)

fclean: fc
	@$(foreach dir, $(SUBDIRS), make -C $(dir) fclean &)

re: fclean r

c:
	@rm $(OBJ) 2> /dev/null || true

fc:
	@rm $(NAME) 2> /dev/null || true

r: clean all
