#ifndef _UTILS_H
# define _UTILS_H

# include <pthread.h>
# include "philosophers.h"

struct s_philosopher;
struct s_table;

void			ft_putstr_fd(char const *s, int fd);
void			ft_putstr_buff(char const *s, char buff[], int *index);
int				ft_atoi(char *str);
void			ft_putnb_buff(int num, char buff[], int *index);
int				ft_is_numeric(char *str);

unsigned long	get_time(unsigned long simulation_start);

void			status_print(char *status, struct s_philosopher *philosopher);
int				stop_simulation_get(struct s_table *table);
void			stop_simulation_set(struct s_table *table);

#endif
