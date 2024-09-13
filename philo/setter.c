#include "philo.h"

void	set_time(pthread_mutex_t *lock, t_ulong *time, t_ulong value)
{
	pthread_mutex_lock(lock);
	*time = value;
	pthread_mutex_unlock(lock);
}

t_ulong	get_timestamp(const t_philo *philo)
{
	t_ulong	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->timestamp;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}

int	get_thread_count(int *count, pthread_mutex_t *lock)
{
	int	rval;

	pthread_mutex_lock(lock);
	rval = *count;	
	pthread_mutex_unlock(lock);
	return (rval);
}

void	decrease_thread_count(int *count, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*count = *count - 1;
	pthread_mutex_unlock(lock);
}

void	sync_threads(t_philo *philo)
{
	decrease_thread_count(&philo->stats->thread_count, philo->stats->lock);
	while(get_thread_count(&philo->stats->thread_count, philo->stats->lock));
}