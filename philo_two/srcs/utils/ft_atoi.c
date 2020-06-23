/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:59:33 by mle-moni          #+#    #+#             */
/*   Updated: 2020/06/11 14:22:52 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	my_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	get_index(char *base, char c)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi(char *str)
{
	int		res;
	int		i;
	int		sign;
	char	*base_deci;

	base_deci = "0123456789";
	res = 0;
	i = 0;
	sign = 1;
	while (my_isspace(str[i]))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		sign *= (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (get_index(base_deci, str[i]));
		i++;
	}
	return (res * sign);
}
