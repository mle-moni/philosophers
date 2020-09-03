/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:44:08 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 22:19:24 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putstr_buff(char const *s, char buff[], int *index)
{
	int		i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		buff[*index] = s[i];
		*index = *index + 1;
		i++;
	}
	buff[*index] = '\0';
}

void	ft_putnb_buff(int num, char buff[], int *index)
{
	char		c;

	if (num < 0)
	{
		num *= -1;
		buff[*index] = '-';
		*index = *index + 1;
	}
	if (num < 10)
	{
		c = '0' + num;
		buff[*index] = c;
		*index = *index + 1;
	}
	else
	{
		ft_putnb_buff(num / 10, buff, index);
		ft_putnb_buff(num % 10, buff, index);
	}
}

int		ft_is_numeric(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i);
}
