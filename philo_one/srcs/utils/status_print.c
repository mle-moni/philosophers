#include "utils.h"

void	status_print(unsigned long timestamp,
int index, char *status, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);

	ft_putnb((int)timestamp);
	ft_putstr_fd(" philosopher no ", 1);
	ft_putnb(index);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(status, 1);
	ft_putstr_fd("\n", 1);
	
	pthread_mutex_unlock(mutex);
}