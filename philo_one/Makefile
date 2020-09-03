# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 14:20:54 by mle-moni          #+#    #+#              #
#    Updated: 2020/09/03 22:44:06 by mayeul           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		philo_one
SRCS =		philosophers.c		\
			utils.c				\
			basic_fn.c			\
			ft_atoi.c			\
			setup.c				\
			set_philosophers.c	\
			mutex_init.c		\
			threads.c			\
			end_simulation.c	\
			philo_routine.c		\
			monitor_routine.c	\
			timing.c			\
			status_print.c		\

OBJS =		$(SRCS:%.c=%.o)

CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
DEBUG =		-Wall -Wextra -Werror -g3 -fsanitize=address

CURRENT_FLAGS = $(DEBUG)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CURRENT_FLAGS) $(OBJS) -o $(NAME) -lpthread

.c.o:
			$(CC) -c $(CURRENT_FLAGS) $< -o $(<:.c=.o)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

norm:
			norminette $(SRCS)

.PHONY:		all re norm clean fclean
