#include "philo.h"

void	set_time(pthread_mutex_t *lock, size_t *time, size_t value)
{
	pthread_mutex_lock(lock);
	*time = value;
	pthread_mutex_unlock(lock);
}

size_t	get_timestamp(const t_philo *philo)
{
	size_t	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->timestamp;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}
