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
	char	buff[128];
	int		idx;

	idx = 0;
	philo->number_of_meals = 0;
	philo->index = i;
	philo->is_up = 0;
	philo->monitor_is_up = 0;
	philo->running = 1;
	philo->limit = 0;
	philo->table = table;
	ft_putstr_buff("/philo_", buff, &idx);
	ft_putnb_buff(philo->index, buff, &idx);
	buff[idx] = '\0';
	sem_unlink(buff);
	philo->mutex = sem_open(buff, O_CREAT, S_IRWXU, 1);
	if (philo->mutex == SEM_FAILED)
		return (1);
	return (0);
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
				free_philo_semaphore(philo);
				i--;
			}
			free(table->men);
			return (1);
		}
		i++;
	}
	return (0);
}
