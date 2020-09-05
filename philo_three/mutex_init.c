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
	sem_unlink("/forks");
	table->mutexes.forks = sem_open("/forks", O_CREAT, S_IRWXU,
	table->philo_number);
	if (table->mutexes.forks == SEM_FAILED)
	{
		free(table->men);
		return (1);
	}
	return (0);
}

int			mutex_init(t_table *table)
{
	sem_unlink("/write");
	table->mutexes.write = sem_open("/write", O_CREAT, S_IRWXU, 1);
	if (table->mutexes.write == SEM_FAILED)
	{
		free(table->men);
		return (1);
	}
	sem_unlink("/prelock");
	table->mutexes.prelock = sem_open("/prelock", O_CREAT, S_IRWXU, 1);
	if (table->mutexes.prelock == SEM_FAILED)
	{
		sem_close(table->mutexes.write);
		sem_unlink("/write");
		free(table->men);
		return (1);
	}
	return (init_forks(table));
}
