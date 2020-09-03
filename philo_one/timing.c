/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 20:51:02 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 22:09:50 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_timing	get_time(t_timing simulation_start)
{
	struct timeval	tv;
	t_timing		result;

	gettimeofday(&tv, NULL);
	result = tv.tv_usec;
	result /= 1000;
	result += (tv.tv_sec * 1000);
	return (result - simulation_start);
}

void		sleep_ms(t_timing ms)
{
	t_timing	sleep_until;

	sleep_until = get_time(0) + ms;
	while (get_time(0) < sleep_until)
	{
		usleep(500);
	}
}
