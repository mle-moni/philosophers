#include "philosophers.h"

int		lock_forks(t_philosopher *philosopher)
{
	sem_wait(philosopher->table->mutexes.forks);
	status_print("has taken a fork", philosopher);
	sem_wait(philosopher->table->mutexes.forks);
	status_print("has taken a fork", philosopher);
	return (0);
}

int		philo_eat(t_philosopher *philosopher)
{
	sem_wait(philosopher->mutex);
	philosopher->last_meal_time = get_time(philosopher->table->simulation_start);
	sem_post(philosopher->mutex);

	philosopher->number_of_meals++;
	status_print("is eating", philosopher);
	usleep(philosopher->table->opts->time_to_eat * 1000);
	sem_post(philosopher->table->mutexes.forks);
	sem_post(philosopher->table->mutexes.forks);
	if (philosopher->number_of_meals == philosopher->table->opts->number_of_times_each_philosopher_must_eat)
		exit(0);
	return (0);
}

int		philo_sleep(t_philosopher *philosopher)
{
	status_print("is sleeping", philosopher);
	if (philosopher->table->opts->number_of_times_each_philosopher_must_eat
	== philosopher->number_of_meals)
	{
		sem_wait(philosopher->table->philo_ready_mutex);
		philosopher->table->philosophers_ready++;
		sem_post(philosopher->table->philo_ready_mutex);
	}
	usleep(philosopher->table->opts->time_to_sleep * 1000);
	return (0);
}