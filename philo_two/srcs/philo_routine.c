#include "philosophers.h"

void			philo_eat_sleep_think(t_philosopher *philosopher)
{
	int				waiting_time;

	if (lock_forks(philosopher))
		return ;
	/* now that the philosopher has the forks
	** he must eat
	*/
	if (philo_eat(philosopher))
		return ;	
	if (philo_sleep(philosopher))
		return ;
	status_print("is thinking", philosopher);
	waiting_time = ((philosopher->table->opts->time_to_die - philosopher->table->opts->time_to_sleep) / 4);
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
