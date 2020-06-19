#include "philosophers.h"

static int	join_threads(t_options *opts, pthread_t *threads)
{
	int		i;

	i = 0;
	while (i < opts->number_of_philosophers)
	{
		if (pthread_join(threads[i], NULL))
		{
			ft_putstr_fd("could not pthread_join philosopher\n", 2);
			return(4);
		}
		i++;
	}
	if (pthread_join(threads[opts->number_of_philosophers], NULL))
	{
		ft_putstr_fd("could not pthread_join monitor thread\n", 2);
		return(4);
	}
	return (0);
}

static void	free_memory(t_table *table, pthread_t *threads)
{
	free(table->philosophers);
	free(threads);
	free(table->mutexes.forks);
	free(table->fork_map);
}

static int	detroy_mutexes(t_options *opts, t_table *table)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < opts->number_of_philosophers)
	{
		ret += pthread_mutex_destroy(&(table->mutexes.forks[i]));
		ret += pthread_mutex_destroy(&table->philosophers[i].mutex);
		i++;
	}
	ret += pthread_mutex_destroy(&table->mutexes.status);
	ret += pthread_mutex_destroy(&table->mutexes.stop_simu);
	ret += pthread_mutex_destroy(&table->mutexes.fork_map);
	ret += pthread_mutex_destroy(&table->philo_ready_mutex);
	return (ret);
}

int			end_simulation(t_options *opts, t_table *table, pthread_t *threads)
{
	int		err;

	err = 0;
	err += join_threads(opts, threads);
	if (detroy_mutexes(opts, table))
	{
		ft_putstr_fd("could not correctly detroy mutexes\n", 2);
		err = 4;
	}
	free_memory(table, threads);
	return (err);
}
