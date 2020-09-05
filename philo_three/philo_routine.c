/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 20:08:17 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 22:52:49 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	philo_eat(t_philosopher *philo)
{
	int		number_of_meals;
	t_table	*table;

	table = philo->table;
	sem_wait(table->mutexes.prelock);
	sem_wait(table->mutexes.forks);
	status_print("has taken a fork", philo);
	sem_wait(table->mutexes.forks);
	status_print("has taken a fork", philo);
	sem_post(table->mutexes.prelock);
	status_print("is eating", philo);
	sem_wait(philo->mutex);
	philo->number_of_meals++;
	number_of_meals = philo->number_of_meals;
	philo->limit = get_time(0) + table->time_to_die;
	sem_post(philo->mutex);
	sleep_ms(table->time_to_eat);
	sem_post(table->mutexes.forks);
	sem_post(table->mutexes.forks);
	return (number_of_meals);
}

static void	philo_sleep_think(t_philosopher *philo)
{
	status_print("is sleeping", philo);
	sleep_ms(philo->table->time_to_sleep);
	status_print("is thinking", philo);
}

static int	create_monitor(t_philosopher *philo)
{
	if (pthread_create(&(philo->monitor), NULL, monitor_routine, philo))
		return (1);
	return (0);
}

void		*philo_routine(void *param)
{
	t_philosopher	*philo;
	t_table			*table;

	philo = param;
	table = philo->table;
	if (create_monitor(philo))
		return (NULL);
	while (1)
	{
		if (philo_eat(philo) == table->times_philo_must_eat)
		{
			philo->running = 0;
			if (philo->monitor_is_up)
				pthread_join(philo->monitor, NULL);
			free_memory(table);
			exit(0);
		}
		philo_sleep_think(philo);
	}
	return (NULL);
}
