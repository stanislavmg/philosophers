#include "philo.h"

void	*monitoring(void *arg)
{
	int	i;
	int num;
	t_philo *philo;

	i = -1;
	philo = (t_philo *)arg;
	num = philo->stats->philo_num;
	while (++i < num)
		pthread_mutex_lock(philo[i].lock);
	usleep(IN_MICROSEC(1000));
	i = -1;
	while (++i < num)
	{
		philo[i].timestamp = gettime(1);
		philo[i].lastmeal = philo[i].timestamp;
		pthread_mutex_unlock(philo[i].lock);
	}
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