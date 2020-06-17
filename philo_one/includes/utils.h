#ifndef _UTILS_H
# define _UTILS_H

#include <pthread.h>
#include "philosophers.h"

struct s_philosopher;
struct s_table;

void			ft_putstr_fd(char const *s, int fd);
int				ft_atoi(char *str);
void			ft_putnb(int number);

unsigned long	get_time(unsigned long simulation_start);

void			status_print(char *status, struct s_philosopher *philosopher);
int				stop_simulation_get(struct s_table *table);
void			stop_simulation_set(struct s_table *table);

int				get_right_fork_id(struct s_philosopher *philosopher);
int				get_left_fork_id(struct s_philosopher *philosopher);
pthread_mutex_t	*get_right_fork(struct s_philosopher *philosopher);
pthread_mutex_t	*get_left_fork(struct s_philosopher *philosopher);

#endif
