NAME := ./suduku_solve

SRCS := mainu.c \
	solver_Sudoku.c\
	strsplit.c \
	test_chiffre.c \
	case_vide.c \
	shuffle_range.c \
	remove.c \
	idiot_solver.c \
	gridass.c \
	celib_nu.c \
	celib_cache.c \
	segment.c \
	segment_2.c \

OBJS := $(SRCS:.c=.o)

CC  := gcc
CFLAGS := -Wall -Wextra
RM := rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

test : $(NAME)
	$(NAME) grille

clean:
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re: fclean all