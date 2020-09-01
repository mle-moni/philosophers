#ifndef _PHILOSOPHERS_H
# define _PHILOSOPHERS_H

# include "utils.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# define DEBUG 0

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
	pthread_mutex_t	mutex;
	pthread_t		*thread;
	struct	s_table	*table;
}				t_philosopher;

typedef struct	s_mutexes
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	status;
	pthread_mutex_t	stop_simu;
	pthread_mutex_t fork_map;
}				t_mutexes;

typedef struct	s_table
{
	int				stop;
	unsigned long	simulation_start;
	int				philosophers_ready;
	int				*fork_map;
	pthread_mutex_t	philo_ready_mutex;
	t_philosopher	*philosophers;
	t_mutexes		mutexes;
	t_options		*opts;
}				t_table;

/* table.mutexes is an array of number_of_forks + 1 mutex
** the additionnal mutex is the one used for writing safely to the stdout
*/

void			*philo_routine(void *param);
void			*verif_routine(void *param);

int				check_parameters(int ac, char **av);
int				set_parameters(int ac, char **av, t_options *opts);

int				memory_allocation(t_options *opts, t_table *table, pthread_t **threads);
int				mutex_init(t_options *opts, t_table *table);
int				table_init(t_options *opts, t_table *table, pthread_t *threads);
int				create_threads(t_options *opts, t_table *table, pthread_t *threads);
int				end_simulation(t_options *opts, t_table *table, pthread_t *threads);

int				lock_forks(t_philosopher *philosopher, pthread_mutex_t	*left_fork_mutex,
pthread_mutex_t	*right_fork_mutex);
int				philo_eat(t_philosopher *philosopher, pthread_mutex_t	*left_fork_mutex,
pthread_mutex_t	*right_fork_mutex);
int				philo_sleep(t_philosopher *philosopher);

#endif
