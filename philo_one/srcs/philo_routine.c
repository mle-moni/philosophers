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

	left_fork_mutex = get_left_fork(philosopher);
	right_fork_mutex = get_right_fork(philosopher);
	pthread_mutex_lock(left_fork_mutex);
	status_print("has taken a fork", philosopher);
	pthread_mutex_lock(right_fork_mutex);
	status_print("has taken a fork", philosopher);
	/* now that the philosopher has the forks
	** he must eat
	*/
	status_print("is eating", philosopher);
	usleep(philosopher->table->opts->time_to_eat * 1000);
	philosopher->last_meal_time = get_time(philosopher->table->simulation_start);
	pthread_mutex_unlock(left_fork_mutex);
	pthread_mutex_unlock(right_fork_mutex);
	status_print("is sleeping", philosopher);
	usleep(philosopher->table->opts->time_to_sleep * 1000);
}

void			*philo_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)param;

	philo_eat(philosopher);

	return (NULL);
}