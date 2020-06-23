#include "philosophers.h"

static void	check_meal_goal_reached(t_table *table)
{
	pthread_mutex_lock(&table->philo_ready_mutex);
	if (table->philosophers_ready >= table->opts->number_of_philosophers)
	{
		stop_simulation_set(table);
		usleep(10 * 1000);
		ft_putstr_fd("number_of_times_each_philosopher_must_eat reached!\n", 1);
	}
	pthread_mutex_unlock(&table->philo_ready_mutex);
}

static void	check_philosophers(t_table *table)
{
	t_philosopher	*philo;
	int				now;
	int				i;

	i = 0;
	while (i < table->opts->number_of_philosophers && stop_simulation_get(table) == 0)
	{
		philo = &(table->philosophers[i]);
		pthread_mutex_lock(&philo->mutex);
		now = (int)get_time(table->simulation_start);
		if (now - philo->last_meal_time > table->opts->time_to_die)
		{
			stop_simulation_set(table);
			status_print("died", philo);
		}
		pthread_mutex_unlock(&philo->mutex);
		i++;
	}
}

void		*verif_routine(void *param)
{
	t_table	*table;

	table = (t_table*)param;
	while (stop_simulation_get(table) == 0)
	// while (3 == 0)
	{
		check_philosophers(table);
		check_meal_goal_reached(table);
	}
	return (NULL);
}
