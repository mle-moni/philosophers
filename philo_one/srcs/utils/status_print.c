#include "utils.h"
#include "philosophers.h"

void	status_print(char *status, t_philosopher *philosopher)
{
	char			buff[256];
	pthread_mutex_t	*mutex;
	int				buff_index;

	memset(buff, 0, 256);
	buff_index = 0;
	mutex = &(philosopher->table->mutexes.status);

	pthread_mutex_lock(mutex);

	ft_putnb_buff(get_time(philosopher->table->simulation_start), buff, &buff_index);
	ft_putstr_buff(" philosopher no ", buff, &buff_index);
	ft_putnb_buff(philosopher->index, buff, &buff_index);
	ft_putstr_buff(": ", buff, &buff_index);
	ft_putstr_buff(status, buff, &buff_index);

	ft_putstr_buff(" (number of meals: ", buff, &buff_index);
	ft_putnb_buff(philosopher->number_of_meals, buff, &buff_index);
	ft_putstr_buff(" / ", buff, &buff_index);
	ft_putnb_buff(philosopher->table->opts->number_of_times_each_philosopher_must_eat, buff, &buff_index);
	ft_putstr_buff(")\n", buff, &buff_index);

	ft_putstr_fd(buff, 1);
	
	pthread_mutex_unlock(mutex);
}
