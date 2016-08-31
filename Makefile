NAME1		= bsq
NAME2		= test_in
FILENAME1	= errorchecked.c
FILENAME2	= tester.c

CC 			= gcc
CFLAGS		= -Wall -Wextra -Werror

all: $(NAME1)
	
$(NAME1):
	$(CC) $(CFLAGS) -o $(NAME1) $(FILENAME1)

$(NAME2):
	$(CC) $(CFLAGS) -o $(NAME2) $(FILENAME2)

fclean:
	rm -f $(NAME1) $(NAME2)

re: fclean all
