/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:44:03 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 20:05:42 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	quit_with_err(const char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int			main(int ac, char **av)
{
	t_table		table;

	if (check_parameters(ac, av))
		return (quit_with_err("Bad parameters!\n"));
	if (set_parameters(ac, av, &table))
		return (quit_with_err("Failed to set parameters\n"));
	if (table.times_philo_must_eat == 0)
		return (0);
	if (setup(&table))
		return (quit_with_err("Error while running the setup!\n"));
	if (end_simulation(&table))
		return (quit_with_err("Error while ending simulation!\n"));
	return (0);
}
