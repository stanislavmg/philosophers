#include "philo.h"

void	*monitoring(void *arg)
{
	int	i;
	int num;
	t_philo *philo;

	philo = (t_philo *)arg;
	num = philo->stats->philo_num;
	i = -1;
	while (1)
	{
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(philo[i].lock);
			if (philo[i].status == DEAD)
			{
				*philo->exp = 1;
				printf("Monitor message: Philosopher #%d dead\n", philo[i].index);
				pthread_mutex_unlock(philo[i].lock);
				i = 0;
				while (i < num)
				{
					pthread_mutex_lock(philo[i].lock);
					philo[i].status = DEAD;
					pthread_mutex_unlock(philo[i].lock);
					i++;
				}
				return (NULL);
			}
			// if (philo->eat_count >= philo->stats->eat_limit && philo->stats->eat_limit != UNDEFINED)
			// 	return (NULL);
			pthread_mutex_unlock(philo[i].lock);
			i++;
		}
	}
	return (NULL);
}