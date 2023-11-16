CC := cc 
CFLAGS := -Wall -Wextra -Werror
INCLUDE := parsing.h
SRCS := cd1.c echo1.c env_to_char.c env1.c env2.c execution_path.c execution.c exit1.c \
expand_heredoc.c expand_utils.c expand.c export_syntax.c export_utils.c export_utils2.c export1.c pwd1.c signals.c syntax_analyser.c \
tokener.c tokener2.c unset1.c utils.c utils2.c utils3.c cd2.c execution_path2.c builtins_aux.c builtins.c main.c \
exec_aux1.c exec_aux2.c exec_aux3.c export_utils3.c utils4.c utils5.c utils6.c utils7.c tokener2_aux.c tokener2_aux2.c\
tokener2_aux3.c tokener_aux.c tokener_aux2.c tokener_aux3.c tokener_aux4.c syn_1.c syn2.c syn3.c leaks_collect.c \
utils8.c
OBJS := $(SRCS:.c=.o)
EXEC := minishell
COMP = $(shell brew --prefix readline)/lib
LINK = $(shell brew --prefix readline)/include

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lreadline -L $(COMP)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -I $(LINK) -c  $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re : fclean all
.PHONY: all clean fclean