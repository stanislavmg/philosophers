#include "philo.h"

static int	check_full(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->stats->philo_num)
	{
		if (philo[i].status != FULL)
			return (0);
	}
	return (1);
}

void	*monitoring(void *arg)
{
	int	i;
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		i = -1;
		if (check_full(philo))
			break ;
		while (++i < philo->stats->philo_num)
		{
			if (DEAD == philo[i].status)
			{ 
				if (pthread_mutex_lock(philo->lock_write))
				 	return NULL;
				i = -1;
				while (++i < philo->stats->philo_num)
					philo[i].status = STOP;
				pthread_mutex_unlock(philo->lock_write);
				return (NULL);
			}
		}
	}
	return (NULL);
}