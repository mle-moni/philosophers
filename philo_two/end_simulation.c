/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:47:01 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 22:49:37 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_memory(t_table *table)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(&(table->mutexes.write));
	while (i < table->philo_number)
	{
		pthread_mutex_destroy(&(table->mutexes.forks[i]));
		pthread_mutex_destroy(&(table->men[i].mutex));
		i++;
	}
	free(table->mutexes.forks);
	free(table->men);
}

int			end_simulation(t_table *table)
{
	join_philosophers(table);
	free_memory(table);
	return (0);
}
