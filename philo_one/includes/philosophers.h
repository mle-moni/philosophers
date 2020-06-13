#ifndef _PHILOSOPHERS_H
# define _PHILOSOPHERS_H

#include "utils.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_options
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_sleep;
	int	time_to_eat;
	int	number_of_times_each_philosopher_must_eat;
}				t_options;

struct	s_table;

typedef struct	s_philosopher
{
	int				index;
	int				last_meal_time;
	int				number_of_meals;
	pthread_t		*thread;
	struct	s_table	*table;
}				t_philosopher;

typedef struct	s_table
{
	int				simulation_start;
	int				forks_num;
	t_philosopher	*philosophers;
	pthread_mutex_t	*mutexes;
	t_options		*opts;
}				t_table;

/* table.mutexes is an array of number_of_forks + 1 mutex
** the additionnal mutex is the one used for writing safely to the stdout
*/

void			*philo_routine(void *param);

#endif
