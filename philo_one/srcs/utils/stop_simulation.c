#include "utils.h"
#include "philosophers.h"

int		stop_simulation_get(t_table *table)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&table->mutexes.stop_simu);
	stop = table->stop;
	pthread_mutex_unlock(&table->mutexes.stop_simu);
	return (stop);
}

void	stop_simulation_set(t_table *table)
{
	pthread_mutex_lock(&table->mutexes.stop_simu);
	table->stop = 1;
	pthread_mutex_unlock(&table->mutexes.stop_simu);
}
