/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:43:43 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 22:48:36 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *str)
{
	const char	*begining_addr;

	begining_addr = str;
	while (*str)
		str++;
	return (str - begining_addr);
}

int		check_parameters(int ac, char **av)
{
	int		i;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!ft_is_numeric(av[i]))
			return (1);
		if (ft_atoi(av[i]) < 0)
			return (1);
		i++;
	}
	if (ft_atoi(av[1]) > 100)
		return (1);
	if (ac == 6 && ft_atoi(av[5]) < 0)
		return (1);
	return (0);
}

void	print_parameters(int ac, char **av)
{
	ft_putstr_fd("Opts:\n", 1);
	ft_putstr_fd("number_of_philosophers: ", 1);
	ft_putstr_fd(av[1], 1);
	ft_putstr_fd("\ntime_to_die: ", 1);
	ft_putstr_fd(av[2], 1);
	ft_putstr_fd("\ntime_to_eat: ", 1);
	ft_putstr_fd(av[3], 1);
	ft_putstr_fd("\ntime_to_sleep: ", 1);
	ft_putstr_fd(av[4], 1);
	if (ac == 6)
	{
		ft_putstr_fd("\nnumber_of_times_each_philosopher_must_eat: ", 1);
		ft_putstr_fd(av[5], 1);
	}
	ft_putstr_fd("\n\n", 1);
}
