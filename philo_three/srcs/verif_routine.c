#include "philosophers.h"

static void	check_philosopher(t_philosopher	*philo)
{
	int				now;
	int				i;

	i = 0;
	if (stop_simulation_get(philo->table) == 0)
	{
		sem_wait(philo->mutex);
		now = (int)get_time(philo->table->simulation_start);
		if (now - philo->last_meal_time > philo->table->opts->time_to_die)
		{
			if (now - philo->last_meal_time < 10000000) {
				stop_simulation_set(philo->table);
				status_print("died", philo);
				sem_wait(philo->table->mutexes.status); // block acces to printing
				exit(1);
			}
		}
		sem_post(philo->mutex);
		i++;
	}
}

void		*verif_routine(void *param)
{
	t_philosopher	*philo;

	philo = (t_philosopher*)param;
	while (stop_simulation_get(philo->table) == 0)
	{
		check_philosopher(philo);
	}
	return (NULL);
}
