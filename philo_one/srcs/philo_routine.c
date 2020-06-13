#include "philosophers.h"

pthread_mutex_t	*get_right_fork(t_philosopher *philosopher)
{
	if (philosopher->index == philosopher->table->forks_num)
		return (&(philosopher->table->mutexes[0]));
	return (&(philosopher->table->mutexes[philosopher->index]));
}

pthread_mutex_t	*get_left_fork(t_philosopher *philosopher)
{
	return (&(philosopher->table->mutexes[philosopher->index - 1]));
}

void			philo_eat(t_philosopher *philosopher)
{
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*mutexes;

	mutexes = philosopher->table->mutexes;
	left_fork_mutex = get_left_fork(philosopher);
	right_fork_mutex = get_right_fork(philosopher);
	pthread_mutex_lock(left_fork_mutex);
	status_print(get_time(), philosopher->index, "has taken a fork", &(mutexes[philosopher->table->forks_num]));
	pthread_mutex_lock(right_fork_mutex);
	status_print(get_time(), philosopher->index, "has taken a fork", &(mutexes[philosopher->table->forks_num]));
	/* now that the philosopher has the forks
	** he must eat
	*/
	status_print(get_time(), philosopher->index, "is eating", &(mutexes[philosopher->table->forks_num]));
	usleep(philosopher->table->opts->time_to_eat);
	pthread_mutex_unlock(left_fork_mutex);
	pthread_mutex_unlock(right_fork_mutex);
	status_print(get_time(), philosopher->index, "is sleeping", &(mutexes[philosopher->table->forks_num]));
	usleep(philosopher->table->opts->time_to_sleep);
}

void			*philo_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)param;
	
	if (philosopher->last_meal_time == 0)
		philosopher->last_meal_time = get_time();

	philo_eat(philosopher);

	return (NULL);
}