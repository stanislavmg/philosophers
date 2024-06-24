#include "philo.h"

static void	sync_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->stats->philo_num)
		pthread_mutex_lock(philo[i].lock);
	usleep(IN_MICROSEC(100));
	i = -1;
	while (++i < philo->stats->philo_num)
		pthread_mutex_unlock(philo[i].lock);
}

// static int	check_full(t_philo *philo)
// {
// 	int i;

// 	i = -1;
// 	while (++i < philo->stats->philo_num)
// 	{
// 		if (philo[i].status != FULL)
// 			return (0);
// 	}
// 	return (1);
// }

void	*monitoring(void *arg)
{
	int	i;
	t_philo *philo;

	
	philo = (t_philo *)arg;
	sync_threads(philo);
	while (1)
	{
		i = -1;
		// if (check_full(philo))
		// 	break ;
		while (++i < philo->stats->philo_num)
		{
			if (DEAD == philo[i].status)
			{
				pthread_mutex_lock(philo->lock_write);
				i = -1;
				while (++i < philo->stats->philo_num)
				{
					// if (FULL == philo[i].status)
					//  	continue ;
					pthread_mutex_lock(philo[i].lock);
					philo[i].status = STOP;
					printf("Philo #%d locked\n", i + 1);
					i++;
				}
				i = -1;
				while (++i < philo->stats->philo_num)
					pthread_mutex_unlock(philo[i].lock);
				pthread_mutex_unlock(philo->lock_write);
				return (NULL);
			}
		}
	}
	return (NULL);
}

long gettime(int type)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	if (type == 2)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	if (type == 1)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	if (type == 3)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	return (0);
}