#include "philosophers.h"

int			memory_allocation(t_options *opts, t_table *table)
{
	table->philosophers = malloc(opts->number_of_philosophers * sizeof(t_philosopher));
	if (!table->philosophers)
		return (1);
	return (0);
}

int			mutex_init(t_options *opts, t_table *table)
{
	sem_unlink("/status");
	table->mutexes.status = sem_open("/status", O_CREAT, S_IRWXU, 1);
	sem_unlink("/stop_simu");
	table->mutexes.stop_simu = sem_open("/stop_simu", O_CREAT, S_IRWXU, 1);
	sem_unlink("/philo_ready_mutex");
	table->philo_ready_mutex = sem_open("/philo_ready_mutex", O_CREAT, S_IRWXU, 1);
	sem_unlink("/forks");
	table->mutexes.forks = sem_open("/forks", O_CREAT, S_IRWXU, opts->number_of_philosophers);
	return (0);
}

int			table_init(t_options *opts, t_table *table)
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

static void	exit_setup(t_table *table, const char *err, int return_value, int free_it)
{
	if (free_it)
	{
		free(table->philosophers);
		table->philosophers = NULL;
	}
	ft_putstr_fd(err, 2);
	exit(return_value);
}

int			create_processes(t_options *opts, t_table *table)
{
	int			i;
	int			pid;
	pthread_t	thread;

	i = 0;
	sem_wait(table->mutexes.status);
	table->simulation_start = get_time(0);
	while (i < opts->number_of_philosophers)
	{
		if ((pid = fork()) == -1)
		{
			kill_all_processes(table, i);
			exit_setup(table, "Could not create process, exiting now\n", 3, 1);
		}
		if (pid == 0)
		{
			if ((pthread_create(&thread, NULL, verif_routine, &table->philosophers[i])) != 0)
				exit_setup(table, "Could not create thread to verify exit conditions\n", 2, 0);
			philo_routine(&table->philosophers[i]);
		}
		else
			(&table->philosophers[i])->pid = pid;
		i++;
	}
	sem_post(table->mutexes.status);
	return (0);
}
