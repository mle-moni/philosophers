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
	pthread_t	*threads;
	t_table		table;
	int			i;

	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Bad number of parameters!\n", 2);
		return (1);
	}

	opts.number_of_times_each_philosopher_must_eat = -1;
	opts.number_of_philosophers = ft_atoi(av[1]);
	opts.time_to_die = ft_atoi(av[2]);
	opts.time_to_eat = ft_atoi(av[3]);
	opts.time_to_sleep = ft_atoi(av[4]);


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
		opts.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		ft_putstr_fd("\nnumber_of_times_each_philosopher_must_eat: ", 1);
		ft_putstr_fd(av[5], 1);
	}
	ft_putstr_fd("\n\n", 1);

	t_philosopher	*philosophers;

	// TO DO: a function that malloc things and test for enomem and return a boolean
	philosophers = malloc(opts.number_of_philosophers * sizeof(t_philosopher));	
	threads = malloc((opts.number_of_philosophers + 1) * sizeof(pthread_t));

	table.mutexes.forks = malloc(opts.number_of_philosophers * sizeof(pthread_mutex_t));
	table.fork_map = malloc(opts.number_of_philosophers * sizeof(int));
	memset(table.fork_map, 0, opts.number_of_philosophers * sizeof(int));
	i = 0;
	while (i < opts.number_of_philosophers)
	{
		pthread_mutex_init(&(table.mutexes.forks[i]), NULL);
		i++;
	}
	pthread_mutex_init(&table.mutexes.status, NULL);
	pthread_mutex_init(&table.mutexes.stop_simu, NULL);
	pthread_mutex_init(&table.mutexes.fork_map, NULL);
	table.philosophers = philosophers;
	table.opts = &opts;
	table.stop = 0;
	table.philosophers_ready = 0;
	pthread_mutex_init(&table.philo_ready_mutex, NULL);

	(void)table;

	i = 0;
	pthread_mutex_lock(&(table.mutexes.status));
	while (i < opts.number_of_philosophers)
	{
		philosophers[i].index = i + 1;
		philosophers[i].last_meal_time = 0;
		philosophers[i].number_of_meals = 0;
		philosophers[i].thread = &(threads[i]);
		philosophers[i].table = &table;
		pthread_mutex_init(&philosophers[i].mutex, NULL);
		if ((pthread_create(&(threads[i]), NULL, philo_routine, &philosophers[i])) != 0)
		{
			ft_putstr_fd("Could not create thread\n", 2);
			exit(3);
		}
		i++;
	}
	if ((pthread_create(&(threads[opts.number_of_philosophers]), NULL, verif_routine, &table)) != 0)
	{
		ft_putstr_fd("Could not create thread\n", 2);
		exit(3);
	}
	table.simulation_start = get_time(0);
	pthread_mutex_unlock(&(table.mutexes.status));

	i = 0;
	while (i < opts.number_of_philosophers)
	{
		if (pthread_join(threads[i], NULL))
		{
			ft_putstr_fd("could not pthread_join\n", 2);
			exit(3);
		}
		i++;
	}
	pthread_join(threads[opts.number_of_philosophers], NULL);
	free(philosophers);
	free(threads);
	free(table.mutexes.forks);
	free(table.fork_map);

	ft_putstr_fd("End of the program\n", 1);
	
	return (0);
}
