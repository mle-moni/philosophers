#include "utils.h"
#include "philosophers.h"

int		stop_simulation_get(t_table *table)
{
	int	stop;

	stop = 0;
	sem_wait(table->mutexes.stop_simu);
	stop = table->stop;
	sem_post(table->mutexes.stop_simu);
	return (stop);
}

void	stop_simulation_set(t_table *table)
{
	sem_wait(table->mutexes.stop_simu);
	table->stop = 1;
	sem_post(table->mutexes.stop_simu);
}
