#include "philosophers.h"

int			check_parameters(int ac, char **av)
{
	int		i;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		if (!ft_is_numeric(av[i++]))
			return (1);
	}
	if (ft_atoi(av[1]) > 500)
		return (1);
	return (0);
}

static void	print_parameters(int ac, char **av)
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

int			set_parameters(int ac, char **av, t_options *opts)
{
	(void)ac;
	opts->number_of_times_each_philosopher_must_eat = -1;
	opts->number_of_philosophers = ft_atoi(av[1]);
	opts->time_to_die = ft_atoi(av[2]);
	opts->time_to_eat = ft_atoi(av[3]);
	opts->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		opts->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	if (DEBUG)
		print_parameters(ac, av);
	return (0);
}
