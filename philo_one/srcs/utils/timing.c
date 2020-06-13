#include <stdlib.h>
#include <sys/time.h>

unsigned long	get_time(unsigned long simulation_start)
{
	struct timeval	tv;
	unsigned long	ret;

	gettimeofday(&tv, NULL);
	ret = tv.tv_usec;
	ret /= 1000;
	ret += (tv.tv_sec * 1000);
	return (ret - simulation_start);
}
