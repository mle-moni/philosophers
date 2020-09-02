#include "philosophers.h"

static void	fill_buff(char *status, t_philosopher *philosopher, char buff[])
{
	int				buff_index;

	buff_index = 0;
	ft_putnb_buff(get_time(philosopher->table->simulation_start), buff, &buff_index);
	ft_putstr_buff(DEBUG ? " philosopher no " : " ", buff, &buff_index);
	ft_putnb_buff(philosopher->index, buff, &buff_index);
	ft_putstr_buff(DEBUG ? ": " : " ", buff, &buff_index);
	ft_putstr_buff(status, buff, &buff_index);
	if (DEBUG)
	{
		ft_putstr_buff(" (number of meals: ", buff, &buff_index);
		ft_putnb_buff(philosopher->number_of_meals, buff, &buff_index);
		ft_putstr_buff(" / ", buff, &buff_index);
		ft_putnb_buff(philosopher->table->opts->number_of_times_each_philosopher_must_eat, buff, &buff_index);
		ft_putstr_buff(")", buff, &buff_index);
	}
	ft_putstr_buff("\n", buff, &buff_index);
}

void		status_print(char *status, t_philosopher *philosopher)
{
	char			buff[256];

	memset(buff, 0, 256);
	sem_wait(philosopher->table->mutexes.status);
	fill_buff(status, philosopher, buff);
	if (status[0] == 'd' && status[1] == 'i' && status[2] == 'e')
		usleep(1000);
	else if (stop_simulation_get(philosopher->table))
	{
		sem_post(philosopher->table->mutexes.status);
		return ;
	}
	ft_putstr_fd(buff, 1);
	sem_post(philosopher->table->mutexes.status);
}
