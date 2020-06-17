#include "philosophers.h"

int				get_right_fork_id(t_philosopher *philosopher)
{
	if (philosopher->index == philosopher->table->opts->number_of_philosophers)
		return (0);
	return (philosopher->index);
}

int				get_left_fork_id(t_philosopher *philosopher)
{
	return (philosopher->index - 1);
}

pthread_mutex_t	*get_right_fork(t_philosopher *philosopher)
{
	return (&(philosopher->table->mutexes.forks[get_right_fork_id(philosopher)]));
}

pthread_mutex_t	*get_left_fork(t_philosopher *philosopher)
{
	return (&(philosopher->table->mutexes.forks[get_left_fork_id(philosopher)]));
}
