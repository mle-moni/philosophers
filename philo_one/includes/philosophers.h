#ifndef _PHILOSOPHERS_H
# define _PHILOSOPHERS_H

#include "utils.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct	s_options
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	number_of_times_each_philosopher_must_eat;
}				t_options;

typedef struct	s_philosopher
{
	int			index;
	int			last_meal_time;
	int			last_sleep_time;
	int			number_of_meals;
	pthread_t	*thread;
}				t_philosopher;

typedef struct	s_fork
{
	int	index;
}				t_fork;

#endif
