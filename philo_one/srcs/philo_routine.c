#include "philosophers.h"

static int		get_waiting_time(t_philosopher *philosopher)
{
	int		time_to_wait;

	time_to_wait = philosopher->table->opts->time_to_die;
	time_to_wait -= philosopher->table->opts->time_to_sleep;
	time_to_wait -= philosopher->table->opts->time_to_eat;
	return (time_to_wait / 2);
}

void			philo_eat_sleep_think(t_philosopher *philosopher)
{
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	int				waiting_time;

	left_fork_mutex = get_left_fork(philosopher);
	right_fork_mutex = get_right_fork(philosopher);

	if (lock_forks(philosopher, left_fork_mutex, right_fork_mutex))
		return ;
	/* now that the philosopher has the forks
	** he must eat
	*/
	if (philo_eat(philosopher, left_fork_mutex, right_fork_mutex))
		return ;	
	if (philo_sleep(philosopher))
		return ;
	status_print("is thinking", philosopher);
	waiting_time = get_waiting_time(philosopher);
	if (waiting_time < 0)
		return ;
	usleep(waiting_time * 1000);
}

void			*philo_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher*)param;

	while (stop_simulation_get(philosopher->table) == 0)
	{
		philo_eat_sleep_think(philosopher);
	}
	return (NULL);
}
