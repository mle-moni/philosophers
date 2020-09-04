/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayeul <mayeul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 15:43:58 by mayeul            #+#    #+#             */
/*   Updated: 2020/09/03 22:47:04 by mayeul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "utils.h"
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

# define DEBUG 0

struct s_table;
typedef	uint64_t	t_timing;

typedef struct		s_philosopher
{
	int				index;
	t_timing		limit;
	int				number_of_meals;
	struct s_table	*table;
	sem_t			*mutex;
	pthread_t		thread;
	pthread_t		monitor;
	int				monitor_is_up;
	int				is_up;
	int				running;
}					t_philosopher;

typedef struct		s_mutexes
{
	sem_t			*forks;
	sem_t			*prelock;
	sem_t			*write;
}					t_mutexes;

typedef struct		s_table
{
	int				philo_number;
	t_timing		time_to_sleep;
	t_timing		time_to_eat;
	t_timing		time_to_die;
	int				times_philo_must_eat;
	t_mutexes		mutexes;
	int				alive;
	t_timing		simu_start;
	t_philosopher	*men;
}					t_table;

/*
** INIT
*/

int					check_parameters(int ac, char **av);
int					set_parameters(int ac, char **av, t_table *table);
int					set_philosophers(t_table *table);
int					mutex_init(t_table *table);
int					create_monitor(t_philosopher *philo);
int					create_threads(t_table *table);
int					setup(t_table *table);

/*
** WHILE THE SIMULATION IS RUNNING
*/

void				*philo_routine(void *param);
void				*monitor_routine(void *param);

/*
** END SIMULATION
*/

int					join_philosophers(t_table *table);
void				free_philo_semaphore(t_philosopher *philo);
int					end_simulation(t_table *table);

/*
** UTILS
*/

t_timing			get_time(t_timing simulation_start);
void				sleep_ms(t_timing ms);
void				status_print(char *status, t_philosopher *philo);
void				print_parameters(int ac, char **av);

#endif
