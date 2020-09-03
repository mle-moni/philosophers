/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:17:21 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 23:12:04 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			join_threads(t_table *table)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < table->philo_number)
	{
		philo = &(table->men[i]);
		if (philo->is_up)
			pthread_join(philo->thread, NULL);
		i++;
	}
	return (0);
}

int			create_monitor(t_philosopher *philo)
{
	if (pthread_create(&(philo->monitor), NULL, monitor_routine, philo))
		return (1);
	pthread_detach(philo->monitor);
	return (0);
}

int			create_threads(t_table *table)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	table->simu_start = get_time(0);
	while (i < table->philo_number)
	{
		usleep(800);
		philo = &(table->men[i]);
		if (pthread_create(&(philo->thread), NULL, philo_routine, philo))
			return (1);
		philo->is_up = 1;
		i++;
	}
	return (0);
}
