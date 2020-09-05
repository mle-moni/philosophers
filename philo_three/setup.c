/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:43:34 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 20:31:04 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	memory_allocation(t_table *table)
{
	table->men = malloc(table->philo_number * sizeof(t_philosopher));
	if (!table->men)
		return (1);
	return (0);
}

int			setup(t_table *table)
{
	if (memory_allocation(table))
		return (1);
	if (set_philosophers(table))
		return (1);
	if (mutex_init(table))
		return (1);
	if (create_processes(table))
	{
		free_memory(table);
		return (1);
	}
	return (0);
}

int			set_parameters(int ac, char **av, t_table *table)
{
	(void)ac;
	table->times_philo_must_eat = -1;
	table->philo_number = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->times_philo_must_eat = ft_atoi(av[5]);
	if (DEBUG)
		print_parameters(ac, av);
	return (0);
}
