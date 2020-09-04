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

void		*monitor_routine(void *param)
{
	t_philosopher	*philo;
	t_timing		now;
	t_timing		limit;

	philo = param;
	philo->monitor_is_up = 1;
	while (philo->table->alive)
	{
		pthread_mutex_lock(&(philo->mutex));
		limit = philo->limit;
		pthread_mutex_unlock(&(philo->mutex));
		if (!limit)
			limit = philo->table->simu_start + philo->table->time_to_die;
		now = get_time(0);
		if (philo->running == 0)
			break ;
		if (limit < now)
		{
			status_print("died", philo);
			break ;
		}
		usleep(2000);
	}
	return (NULL);
}
