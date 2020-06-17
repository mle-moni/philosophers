#include "utils.h"
#include "philosophers.h"

void	status_print(char *status, t_philosopher *philosopher)
{
	int				index;
	pthread_mutex_t	*mutex;
	unsigned long	timestamp;

	timestamp = get_time(philosopher->table->simulation_start);
	index = philosopher->index;
	mutex = &(philosopher->table->mutexes.status);

	pthread_mutex_lock(mutex);

	ft_putnb((int)timestamp);
	ft_putstr_fd(" philosopher no ", 1);
	ft_putnb(index);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(status, 1);

	ft_putstr_fd(" (number of meals: ", 1);
	ft_putnb(philosopher->number_of_meals);
	ft_putstr_fd(" / ", 1);
	ft_putnb(philosopher->table->opts->number_of_times_each_philosopher_must_eat);
	ft_putstr_fd(")", 1);
	ft_putstr_fd("\n", 1);
	
	pthread_mutex_unlock(mutex);
}
