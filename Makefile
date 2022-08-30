SRCS = pipex.c utils.c utils2.c exec_functions.c error.c 

OBJS = ${SRCS:.c=.o}

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

.c.o:
	cc ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	cc -o ${NAME} ${CFLAGS} ${OBJS} 

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean re
