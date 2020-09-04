/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 19:00:31 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 21:03:11 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_forks(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(&(table->mutexes.forks[i]), NULL))
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&(table->mutexes.forks[i]));
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

int			mutex_init(t_table *table)
{
	if (pthread_mutex_init(&(table->mutexes.write), NULL))
	{
		free(table->mutexes.forks);
		free(table->men);
		return (1);
	}
	return (init_forks(table));
}
