#include "philo.h"

void	*monitoring(void *arg)
{
	int	i;
	int num;
	t_philo *philo;

	philo = (t_philo *)arg;
	num = philo->stats->philo_num;
	while (1)
	{
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(philo[i].lock);
			if (philo->status)
				return (NULL);
			if (philo->eat_count >= philo->stats->eat_limit && philo->stats->eat_limit != UNDEFINED)
				return (NULL);
			pthread_mutex_unlock(philo[i].lock);
		}
	}
	return (NULL);
}