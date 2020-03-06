NAME=librev.a

SRCS=revert_string.c

OBJS=*.o

$(NAME):
	gcc -c $(SRCS) -I revert_string.h
	ar rc $(NAME) $(OBJS)
clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f  $(NAME)

re: fclean all
