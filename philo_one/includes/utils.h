#ifndef _UTILS_H
# define _UTILS_H

#include <pthread.h>

void			ft_putstr_fd(char const *s, int fd);
int				ft_atoi(char *str);
void			ft_putnb(int number);

unsigned long	get_time(void);

void			status_print(unsigned long timestamp,
int index, char *status, pthread_mutex_t *mutex);

#endif
