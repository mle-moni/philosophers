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
	t_table			*table;
	t_timing		now;
	t_timing		limit;

	philo = param;
	table = philo->table;
	while (table->alive)
	{
		pthread_mutex_lock(&(philo->mutex));
		limit = philo->limit;
		pthread_mutex_unlock(&(philo->mutex));
		if (!limit)
			limit = table->simu_start + table->time_to_die;
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
