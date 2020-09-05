/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 20:24:38 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 23:02:49 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_died(t_philosopher *philo)
{
	status_print("died", philo);
	sem_wait(philo->table->mutexes.write);
	exit(1);
}

void		*monitor_routine(void *param)
{
	t_philosopher	*philo;
	t_timing		now;
	t_timing		limit;

	philo = param;
	philo->monitor_is_up = 1;
	while (1)
	{
		sem_wait(philo->mutex);
		limit = philo->limit;
		sem_post(philo->mutex);
		if (!limit)
			limit = philo->table->simu_start + philo->table->time_to_die;
		now = get_time(0);
		if (philo->running == 0)
			break ;
		if (limit < now)
			philo_died(philo);
		usleep(2000);
	}
	return (NULL);
}
