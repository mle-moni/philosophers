#include "philosophers.h"

int		memory_allocation(t_options *opts, t_table *table, pthread_t **threads)
{
	table->philosophers = malloc(opts->number_of_philosophers * sizeof(t_philosopher));
	if (!table->philosophers)
		return (1);
	*threads = malloc((opts->number_of_philosophers + 1) * sizeof(pthread_t));
	if (!*threads)
		return (1);
	return (0);
}

int		mutex_init(t_options *opts, t_table *table)
{
	sem_unlink("/status");
	table->mutexes.status = sem_open("/status", O_CREAT, S_IRWXU, 1);
	sem_unlink("/stop_simu");
	table->mutexes.stop_simu = sem_open("/stop_simu", O_CREAT, S_IRWXU, 1);
	sem_unlink("/philo_ready_mutex");
	table->philo_ready_mutex = sem_open("/philo_ready_mutex", O_CREAT, S_IRWXU, 1);
	sem_unlink("/forks");
	table->mutexes.forks = sem_open("/forks", O_CREAT, S_IRWXU, opts->number_of_philosophers);
	sem_unlink("/forks_avail");
	table->mutexes.forks_avail = sem_open("/forks_avail", O_CREAT, S_IRWXU, 1);
	table->forks_avail = opts->number_of_philosophers;
	return (0);
}

int		table_init(t_options *opts, t_table *table, pthread_t *threads)
{
	int		i;
	char	buff[128];
	int		idx;

	i = 0;
	table->opts = opts;
	table->stop = 0;
	table->philosophers_ready = 0;
	table->simulation_start = 0;

	while (i < opts->number_of_philosophers)
	{
		table->philosophers[i].index = i + 1;
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].number_of_meals = 0;
		table->philosophers[i].thread = &(threads[i]);
		table->philosophers[i].table = table;
		idx = 0;
		ft_putstr_buff("/philo_", buff, &idx);
		ft_putnb_buff(i, buff, &idx);
		buff[idx] = '\0';
		sem_unlink(buff);
		table->philosophers[i].mutex = sem_open(buff, O_CREAT, S_IRWXU, 1);
		i++;
	}
	return (0);
}

int		create_threads(t_options *opts, t_table *table, pthread_t *threads)
{
	int		i;

	i = 0;
	sem_wait(table->mutexes.status);
	while (i < opts->number_of_philosophers)
	{
		if ((pthread_create(&(threads[i]), NULL, philo_routine, &table->philosophers[i])) != 0)
		{
			ft_putstr_fd("Could not create thread\n", 2);
			return(3);
		}
		i++;
	}
	if ((pthread_create(&(threads[opts->number_of_philosophers]), NULL, verif_routine, table)) != 0)
	{
		ft_putstr_fd("Could not create thread\n", 2);
		return(3);
	}
	table->simulation_start = get_time(0);
	sem_post(table->mutexes.status);
	return (0);
}
