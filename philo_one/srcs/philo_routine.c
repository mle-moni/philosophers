#include "philosophers.h"

pthread_mutex_t	*get_right_fork(t_philosopher *philosopher)
{
	if (philosopher->index == philosopher->table->opts->number_of_philosophers)
		return (&(philosopher->table->mutexes.forks[0]));
	return (&(philosopher->table->mutexes.forks[philosopher->index]));
}

pthread_mutex_t	*get_left_fork(t_philosopher *philosopher)
{
	return (&(philosopher->table->mutexes.forks[philosopher->index - 1]));
}

void			philo_eat_sleep_think(t_philosopher *philosopher)
{
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;

	left_fork_mutex = get_left_fork(philosopher);
	right_fork_mutex = get_right_fork(philosopher);
	pthread_mutex_lock(left_fork_mutex);
	if (stop_simulation_get(philosopher->table))
	{
		pthread_mutex_unlock(left_fork_mutex);
		return ;
	}
	status_print("has taken a fork", philosopher);
	pthread_mutex_lock(right_fork_mutex);
	if (stop_simulation_get(philosopher->table))
	{
		pthread_mutex_unlock(right_fork_mutex);
		return ;
	}
	status_print("has taken a fork", philosopher);
	/* now that the philosopher has the forks
	** he must eat
	*/
	status_print("is eating", philosopher);
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->last_meal_time = get_time(philosopher->table->simulation_start);
	pthread_mutex_unlock(&philosopher->mutex);
	usleep(philosopher->table->opts->time_to_eat * 1000);
	philosopher->number_of_meals++;

	pthread_mutex_lock(&philosopher->mutex);
	philosopher->last_meal_time = get_time(philosopher->table->simulation_start);
	pthread_mutex_unlock(&philosopher->mutex);

	pthread_mutex_unlock(left_fork_mutex);
	pthread_mutex_unlock(right_fork_mutex);
	if (stop_simulation_get(philosopher->table))
		return ;
	status_print("is sleeping", philosopher);
	usleep(philosopher->table->opts->time_to_sleep * 1000);
	if (stop_simulation_get(philosopher->table))
		return ;
	status_print("is thinking", philosopher);
}

void			*philo_routine(void *param)
{
	t_philosopher	*philosopher;
	int				number_of_meals_goal;

	philosopher = (t_philosopher*)param;
	number_of_meals_goal = philosopher->table->opts->number_of_times_each_philosopher_must_eat;

	usleep((philosopher->index - 1) * 2000);

	while (stop_simulation_get(philosopher->table) == 0)
	{
		philo_eat_sleep_think(philosopher);

		usleep((philosopher->table->opts->time_to_die / 4) * 1000);

		if (number_of_meals_goal == philosopher->number_of_meals)
		{
			pthread_mutex_lock(&philosopher->table->philo_ready_mutex);
			philosopher->table->philosophers_ready++;
			pthread_mutex_unlock(&philosopher->table->philo_ready_mutex);
		}
	}
	return (NULL);
}