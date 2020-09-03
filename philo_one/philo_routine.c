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
	pthread_mutex_lock(&(table->mutexes.forks[philo->forks.left]));
	status_print("has taken a fork", philo);
	pthread_mutex_lock(&(table->mutexes.forks[philo->forks.right]));
	status_print("has taken a fork", philo);
	status_print("is eating", philo);
	pthread_mutex_lock(&(philo->mutex));
	philo->number_of_meals++;
	number_of_meals = philo->number_of_meals;
	philo->limit = get_time(0) + table->time_to_die;
	pthread_mutex_unlock(&(philo->mutex));
	sleep_ms(table->time_to_eat);
	pthread_mutex_unlock(&(table->mutexes.forks[philo->forks.right]));
	pthread_mutex_unlock(&(table->mutexes.forks[philo->forks.left]));
	return (number_of_meals);
}

static void	philo_sleep_think(t_philosopher *philo)
{
	status_print("is sleeping", philo);
	sleep_ms(philo->table->time_to_sleep);
	status_print("is thinking", philo);
}

void		*philo_routine(void *param)
{
	t_philosopher	*philo;
	t_table			*table;

	philo = param;
	table = philo->table;
	if (create_monitor(philo))
		return (NULL);
	while (table->alive)
	{
		if (philo_eat(philo) == table->times_philo_must_eat)
		{
			philo->running = 0;
			return (NULL);
		}
		philo_sleep_think(philo);
	}
	return (NULL);
}
