#include "philosophers.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#include <stdio.h>

int			detroy_mutexes(t_options *opts, t_table *table)
{
	int		i;
	int		ret;
	char	buff[128];
	int		idx;

	i = 0;
	ret = 0;
	while (i < opts->number_of_philosophers)
	{
		idx = 0;
		ret += sem_close(table->philosophers[i].mutex);
		ft_putstr_buff("/philo_", buff, &idx);
		ft_putnb_buff(i, buff, &idx);
		buff[idx] = '\0';
		sem_unlink(buff);
		i++;
	}
	ret += sem_close(table->mutexes.status);
	sem_unlink("/status");
	ret += sem_close(table->mutexes.stop_simu);
	sem_unlink("/stop_simu");
	ret += sem_close(table->philo_ready_mutex);
	sem_unlink("/philo_ready_mutex");
	ret += sem_close(table->mutexes.forks);
	sem_unlink("/forks");
	return (ret);
}

void		kill_all_processes(t_table *table, int max)
{
	int	i;
	int	pid;

	if (max == 0)
		max = table->opts->number_of_philosophers;
	i = 0;
	while (i < max)
	{
		pid = table->philosophers[i].pid;
		kill(pid, SIGKILL);
		i++;
	}
}

static void	wait_processes(t_table *table)
{
	int		infinite;
	int		retval;
	int		num_of_philo = 0;

	infinite = 1;
	// infinite loop thats waits that one of the process exits, then it kills all others process
	while (infinite)
	{
		if (waitpid(-1, &retval, 0) > 0)
		{
			if (WIFEXITED(retval) && WEXITSTATUS(retval) == 0)
			{
				num_of_philo++;
				if (num_of_philo == table->opts->number_of_philosophers)
				{
					sem_wait(table->mutexes.status); // block acces to printing
					ft_putstr_fd("number_of_times_each_philosopher_must_eat reached!\n", 1);
					infinite = 0;
				}
			}
			else
			{
				kill_all_processes(table, 0);
				infinite = 0;
			}
		}
	}
}

int			end_simulation(t_options *opts, t_table *table)
{
	int		err;

	wait_processes(table);
	err = 0;
	if (detroy_mutexes(opts, table))
	{
		ft_putstr_fd("could not correctly detroy mutexes\n", 2);
		err = 4;
	}
	free(table->philosophers);
	return (err);
}
