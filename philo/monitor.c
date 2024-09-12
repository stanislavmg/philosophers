#include "philo.h"

void	set_status(t_philo *philo, int status_)
{
	pthread_mutex_lock(philo->lock);
	philo->status = status_;
	pthread_mutex_unlock(philo->lock);
}

int	get_status(t_philo *philo)
{
	int	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->status;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}

static int	check_full(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->stats->philo_num)
	{
		if (get_status(philo + i) != FULL)
			return (0);
	}
	return (1);
}

size_t	get_lastmeal(t_philo *philo)
{
	size_t	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->lastmeal;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}

void	*monitoring(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_usleep(200);
	while (!check_full(philo))
	{
		i = -1;
		while (++i < philo->stats->philo_num)
		{
			if (cmp_time(philo + i))
			{
				pthread_mutex_lock(philo->write);
				set_status(philo + i, DEAD);
				printf("%ld %d is died\n", gettime() - get_timestamp(philo), i + 1);
				pthread_mutex_unlock(philo->write);
			}
			if (DEAD == get_status(philo + i))
			{
				pthread_mutex_lock(philo->write);
				i = -1;
				while (++i < philo->stats->philo_num)
					set_status(philo + i, STOP);
				pthread_mutex_unlock(philo->write);
				return (NULL);
			}
		}
	}
	return (NULL);
}
