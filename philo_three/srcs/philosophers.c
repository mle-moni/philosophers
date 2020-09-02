/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:00:59 by mle-moni          #+#    #+#             */
/*   Updated: 2020/06/11 15:55:15 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* OPTIONS:
** number_of_philosophers time_to_die
** time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
*/

int			main(int ac, char **av)
{
	t_options	opts;
	t_table		table;

	if (check_parameters(ac, av))
	{
		ft_putstr_fd("Bad parameters!\n", 2);
		return (1);
	}
	set_parameters(ac, av, &opts);
	if (memory_allocation(&opts, &table))
	{
		ft_putstr_fd("memory allocation failed\n", 2);
		return (2);
	}
	mutex_init(&opts, &table);
	table_init(&opts, &table);
	if (create_processes(&opts, &table))
		return (3);
	if (end_simulation(&opts, &table))
		return (4);
	return (0);
}
