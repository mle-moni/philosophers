/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:43:48 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 15:43:48 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>

int		check_parameters(int ac, char **av);

size_t	ft_strlen(const char *str);
int		ft_is_numeric(char *str);
int		ft_atoi(char *str);

void	ft_putnb_buff(int num, char buff[], int *index);
void	ft_putstr_buff(char const *s, char buff[], int *index);
void	ft_putstr_fd(char const *s, int fd);

#endif