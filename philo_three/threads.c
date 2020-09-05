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

static int	kill_all_processes(t_table *table, int max, int ret)
{
	int	i;
	int	pid;

	if (max == 0)
		max = table->philo_number;
	i = 0;
	while (i < max)
	{
		pid = table->men[i].pid;
		kill(pid, SIGKILL);
		i++;
	}
	return (ret);
}

void		wait_philosophers(t_table *table)
{
	int		retval;
	int		num_of_philo;

	num_of_philo = 0;
	while (num_of_philo < table->philo_number)
	{
		if (waitpid(-1, &retval, 0) > 0)
		{
			if (WIFEXITED(retval) && WEXITSTATUS(retval) == 0)
				num_of_philo++;
			else
			{
				kill_all_processes(table, 0, 0);
				sem_post(table->mutexes.write);
				break ;
			}
		}
	}
}

int			create_processes(t_table *table)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	table->simu_start = get_time(0);
	while (i < table->philo_number)
	{
		usleep(800);
		philo = &(table->men[i]);
		if ((philo->pid = fork()) == -1)
			return (kill_all_processes(table, i - 1, 2));
		if (philo->pid == 0)
			philo_routine(philo);
		philo->is_up = 1;
		i++;
	}
	return (0);
}
