#ifndef _PHILOSOPHERS_H
# define _PHILOSOPHERS_H

# include "utils.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

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
	sem_t			*mutex;
	pid_t			pid;
	struct	s_table	*table;
}				t_philosopher;

typedef struct	s_mutexes
{
	sem_t			*forks;
	sem_t			*status;
	sem_t			*stop_simu;
}				t_mutexes;

typedef struct	s_table
{
	int				stop;
	unsigned long	simulation_start;
	int				philosophers_ready;
	sem_t			*philo_ready_mutex;
	t_philosopher	*philosophers;
	t_mutexes		mutexes;
	t_options		*opts;
}				t_table;


void			*philo_routine(void *param);
void			*verif_routine(void *param);

int				check_parameters(int ac, char **av);
int				set_parameters(int ac, char **av, t_options *opts);

int				memory_allocation(t_options *opts, t_table *table);
int				mutex_init(t_options *opts, t_table *table);
int				table_init(t_options *opts, t_table *table);
int				create_processes(t_options *opts, t_table *table);
void			kill_all_processes(t_table *table, int max);
int				detroy_mutexes(t_options *opts, t_table *table);
int				end_simulation(t_options *opts, t_table *table);

int				lock_forks(t_philosopher *philosopher);
int				philo_eat(t_philosopher *philosopher);
int				philo_sleep(t_philosopher *philosopher);

#endif