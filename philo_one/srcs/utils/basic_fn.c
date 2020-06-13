/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:34:16 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/09 13:36:05 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char const *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		i++;
	write(fd, s, i);
}

void	ft_putnb(int number)
{
	long int	num;
	char		c;

	num = number;
	if (num < 0)
	{
		num *= -1;
		write(1, "-", 1);
	}
	if (num < 10)
	{
		c = '0' + num;
		write(1, &c, 1);
	}
	else
	{
		ft_putnb(num / 10);
		ft_putnb(num % 10);
	}
}
