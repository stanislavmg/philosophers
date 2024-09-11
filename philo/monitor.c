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

long	get_lastmeal(t_philo *philo)
{
	long	rval;

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
			if (philo->stats->ttd < (gettime() - get_lastmeal(philo + i)))
			{
				pthread_mutex_lock(philo->write);
				printf("%ld %d is died\n", gettime() - philo->timestamp, i + 1);
				set_status(philo + i, DEAD);
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
