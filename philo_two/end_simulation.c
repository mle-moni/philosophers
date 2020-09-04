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

void		free_philo_semaphore(t_philosopher *philo)
{
	char	buff[128];
	int		idx;

	sem_close(philo->mutex);
	idx = 0;
	ft_putstr_buff("/philo_", buff, &idx);
	ft_putnb_buff(philo->index, buff, &idx);
	buff[idx] = '\0';
	sem_unlink(buff);
}

static void	free_memory(t_table *table)
{
	int		i;

	i = 0;
	sem_close(table->mutexes.write);
	sem_close(table->mutexes.forks);
	sem_close(table->mutexes.prelock);
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/prelock");
	while (i < table->philo_number)
	{
		free_philo_semaphore(&(table->men[i]));
		i++;
	}
	free(table->men);
}

int			end_simulation(t_table *table)
{
	join_philosophers(table);
	free_memory(table);
	return (0);
}
