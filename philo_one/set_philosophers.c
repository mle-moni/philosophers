/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philosophers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:17:00 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 23:01:56 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	set_philosopher(t_philosopher *philo, t_table *table, int i)
{
	philo->number_of_meals = 0;
	philo->index = i;
	philo->forks.left = i;
	philo->forks.right = (i + 1) % table->philo_number;
	philo->is_up = 0;
	philo->monitor_is_up = 0;
	philo->running = 1;
	philo->limit = 0;
	philo->table = table;
	return (pthread_mutex_init(&philo->mutex, NULL));
}

int			set_philosophers(t_table *table)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < table->philo_number)
	{
		philo = &(table->men[i]);
		if (set_philosopher(philo, table, i))
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&(philo->mutex));
				i--;
			}
			free(table->mutexes.forks);
			free(table->men);
			return (1);
		}
		i++;
	}
	return (0);
}
