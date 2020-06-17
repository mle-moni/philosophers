#include "philosophers.h"

void			philo_eat_sleep_think(t_philosopher *philosopher)
{
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;

	left_fork_mutex = get_left_fork(philosopher);
	right_fork_mutex = get_right_fork(philosopher);

	pthread_mutex_lock(&philosopher->table->mutexes.fork_map);
	if (philosopher->table->fork_map[get_left_fork_id(philosopher)] ||
	philosopher->table->fork_map[get_right_fork_id(philosopher)])
	{
		pthread_mutex_unlock(&philosopher->table->mutexes.fork_map);
		usleep(1000);
		return ;
	}
	philosopher->table->fork_map[get_left_fork_id(philosopher)] = 1;
	philosopher->table->fork_map[get_right_fork_id(philosopher)] = 1;
	pthread_mutex_unlock(&philosopher->table->mutexes.fork_map);

	if (stop_simulation_get(philosopher->table))
	{
		pthread_mutex_unlock(right_fork_mutex);
		return ;
	}
	pthread_mutex_lock(left_fork_mutex);
	status_print("has taken a fork", philosopher);
	pthread_mutex_lock(right_fork_mutex);
	status_print("has taken a fork", philosopher);
	/* now that the philosopher has the forks
	** he must eat
	*/
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
	// usleep((philosopher->table->opts->time_to_die / 2) * 1000);
}

void			*philo_routine(void *param)
{
	t_philosopher	*philosopher;
	int				number_of_meals_goal;

	philosopher = (t_philosopher*)param;
	number_of_meals_goal = philosopher->table->opts->number_of_times_each_philosopher_must_eat;

	usleep((philosopher->index - 1) * 1000);

	while (stop_simulation_get(philosopher->table) == 0)
	{
		philo_eat_sleep_think(philosopher);

		if (number_of_meals_goal == philosopher->number_of_meals)
		{
			pthread_mutex_lock(&philosopher->table->philo_ready_mutex);
			philosopher->table->philosophers_ready++;
			pthread_mutex_unlock(&philosopher->table->philo_ready_mutex);
		}
	}
	return (NULL);
}

/*
** MUTEX FORK MAP ARRAY (+ QUEUE SYSTEM (maybe))
** (4 forks, 1 = used, 0 = free)
** [0, 0, 1, 0]
*/