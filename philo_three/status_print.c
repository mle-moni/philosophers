/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 22:14:44 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 22:31:49 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	fill_buff(char *status, t_philosopher *philosopher, char buff[])
{
	int				buff_index;

	buff_index = 0;
	ft_putnb_buff(get_time(philosopher->table->simu_start), buff, &buff_index);
	ft_putstr_buff(DEBUG ? " philosopher no " : " ", buff, &buff_index);
	ft_putnb_buff(philosopher->index, buff, &buff_index);
	ft_putstr_buff(DEBUG ? ": " : " ", buff, &buff_index);
	ft_putstr_buff(status, buff, &buff_index);
	if (DEBUG)
	{
		ft_putstr_buff(" (number of meals: ", buff, &buff_index);
		ft_putnb_buff(philosopher->number_of_meals, buff, &buff_index);
		ft_putstr_buff(" / ", buff, &buff_index);
		ft_putnb_buff(philosopher->table->times_philo_must_eat,
		buff, &buff_index);
		ft_putstr_buff(")", buff, &buff_index);
	}
	ft_putstr_buff("\n", buff, &buff_index);
}

void		status_print(char *status, t_philosopher *philo)
{
	char			buff[256];

	memset(buff, 0, 256);
	sem_wait(philo->table->mutexes.write);
	fill_buff(status, philo, buff);
	if (status[0] == 'd' && status[1] == 'i' && status[2] == 'e')
		usleep(1000);
	ft_putstr_fd(buff, 1);
	sem_post(philo->table->mutexes.write);
}
