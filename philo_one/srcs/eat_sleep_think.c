#include "philosophers.h"

int		lock_forks(t_philosopher *philosopher, pthread_mutex_t	*left_fork_mutex,
pthread_mutex_t	*right_fork_mutex)
{
	pthread_mutex_lock(&philosopher->table->mutexes.fork_map);
	if (philosopher->table->opts->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(&philosopher->table->mutexes.fork_map);
		return (1);
	}
	if (philosopher->table->fork_map[get_left_fork_id(philosopher)] ||
	philosopher->table->fork_map[get_right_fork_id(philosopher)])
	{
		pthread_mutex_unlock(&philosopher->table->mutexes.fork_map);
		usleep(1000);
		return (1);
	}
	philosopher->table->fork_map[get_left_fork_id(philosopher)] = 1;
	philosopher->table->fork_map[get_right_fork_id(philosopher)] = 1;
	pthread_mutex_unlock(&philosopher->table->mutexes.fork_map);
	pthread_mutex_lock(left_fork_mutex);
	status_print("has taken a fork", philosopher);
	pthread_mutex_lock(right_fork_mutex);
	status_print("has taken a fork", philosopher);
	return (0);
}

int		philo_eat(t_philosopher *philosopher, pthread_mutex_t	*left_fork_mutex,
pthread_mutex_t	*right_fork_mutex)
{
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->last_meal_time = get_time(philosopher->table->simulation_start);
	pthread_mutex_unlock(&philosopher->mutex);

	status_print("is eating", philosopher);
	usleep(philosopher->table->opts->time_to_eat * 1000);
	philosopher->number_of_meals++;

	pthread_mutex_lock(&philosopher->table->mutexes.fork_map);
	philosopher->table->fork_map[get_left_fork_id(philosopher)] = 0;
	philosopher->table->fork_map[get_right_fork_id(philosopher)] = 0;
	pthread_mutex_unlock(&philosopher->table->mutexes.fork_map);

	pthread_mutex_unlock(left_fork_mutex);
	pthread_mutex_unlock(right_fork_mutex);
	return (0);
}

int		philo_sleep(t_philosopher *philosopher)
{
	status_print("is sleeping", philosopher);
	if (philosopher->table->opts->number_of_times_each_philosopher_must_eat
	== philosopher->number_of_meals)
	{
		pthread_mutex_lock(&philosopher->table->philo_ready_mutex);
		philosopher->table->philosophers_ready++;
		pthread_mutex_unlock(&philosopher->table->philo_ready_mutex);
	}
	usleep(philosopher->table->opts->time_to_sleep * 1000);
	return (0);
}
