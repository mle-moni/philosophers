# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 14:20:54 by mle-moni          #+#    #+#              #
#    Updated: 2020/06/11 14:23:25 by mle-moni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		philo_three
SRCS =		srcs/philosophers.c \
			srcs/utils/basic_fn.c \
			srcs/utils/ft_atoi.c \
			srcs/utils/timing.c \
			srcs/utils/status_print.c \
			srcs/utils/stop_simulation.c \
			srcs/philo_routine.c \
			srcs/verif_routine.c \
			srcs/eat_sleep_think.c \
			srcs/parameters.c \
			srcs/setup.c \
			srcs/end_simulation.c \

OBJS =		$(SRCS:%.c=%.o)
DEP = 		$(OBJS:%.o=%.d)

INC_DIR = 	includes/
HEADER = 	$(INC_DIR)philosophers.h \
			$(INC_DIR)utils.h \

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
MAKE = 		make
HFLAGS =	-I $(INC_DIR)
DEBUG =		-Wall -Wextra -Werror -g3 -fsanitize=address
LINUX =		-Wall -Wextra

CURRENT_FLAGS = $(DEBUG)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CURRENT_FLAGS) $(OBJS) -o $(NAME) -pthread

.c.o:
			$(CC) -c $(CURRENT_FLAGS) -MMD -MP $(HFLAGS) $< -o $(<:.c=.o)

clean:
			rm -f $(OBJS) $(DEP)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

norm:
			norminette $(SRCS) $(HEADER)

test:		$(NAME)
			./debug/tests/tester.sh

main:		$(NAME)
			./$(NAME)

.PHONY:		all re norm clean fclean main test

-include 	$(DEP)
