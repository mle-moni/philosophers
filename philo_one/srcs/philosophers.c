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

// DOCS:
// https://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/
// int pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg);

void		*philo_routine(void *param)
{
	pthread_mutex_t	lock;

	philo_routine(param);
}

int			main(int ac, char **av)
{
	t_options	opts;
	pthread_t	*threads;
	int			i;

	i = 0;
	if (ac < 4)
	{
		ft_putstr_fd("Missing parameters!\n", 2);
		return (1);
	}

	opts.number_of_philosophers = ft_atoi(av[1]);
	opts.time_to_die = ft_atoi(av[2]);
	opts.time_to_eat = ft_atoi(av[3]);


	ft_putstr_fd("Opts:\n", 1);
	ft_putstr_fd("number_of_philosophers: ", 1);
	ft_putstr_fd(av[1], 1);
	ft_putstr_fd("\ntime_to_die: ", 1);
	ft_putstr_fd(av[2], 1);
	ft_putstr_fd("\ntime_to_eat: ", 1);
	ft_putstr_fd(av[3], 1);
	if (ac == 5)
	{
		opts.number_of_times_each_philosopher_must_eat = ft_atoi(av[4]);
		ft_putstr_fd("\nnumber_of_times_each_philosopher_must_eat: ", 1);
		ft_putstr_fd(av[4], 1);
	}
	ft_putstr_fd("\n", 1);

	t_philosopher	*philosophers;

	philosophers = malloc(opts.number_of_philosophers * sizeof(t_philosopher));
	
	threads = malloc(opts.number_of_philosophers * sizeof(pthread_t));

	while (i < opts.number_of_philosophers)
	{
		philosophers[i].index = i + 1;
		philosophers[i].last_meal_time = 0;
		philosophers[i].last_sleep_time = 0;
		philosophers[i].number_of_meals = 0;
		philosophers[i].thread = threads[i];
		if ((pthread_create(&(threads[i]), NULL, philo_routine, NULL)) != 0)
		{
			ft_putstr_fd("Could not create thread\n", 1);
			return (2);
		}
	}
	
	return (0);
}
