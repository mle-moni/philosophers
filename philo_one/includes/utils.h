#ifndef _UTILS_H
# define _UTILS_H

#include <pthread.h>
#include "philosophers.h"

struct s_philosopher;

void			ft_putstr_fd(char const *s, int fd);
int				ft_atoi(char *str);
void			ft_putnb(int number);

unsigned long	get_time(unsigned long simulation_start);

void			status_print(char *status, struct s_philosopher *philosopher);

#endif
