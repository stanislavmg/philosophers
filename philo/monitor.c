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

t_ulong	get_lastmeal(t_philo *philo)
{
	t_ulong	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->lastmeal;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}

void	*monitoring(void *arg)
{
	int			i;
	t_philo		*philo;
	t_ulong		tmp;
	t_status	cs;

	philo = (t_philo *)arg;
	tmp = get_timestamp(philo);
	ft_usleep(200);
	while (!check_full(philo))
	{
		i = -1;
		while (++i < philo->stats->philo_num)
		{
			cs = get_status(philo + i);
			if (cmp_time(philo + i) && cs != EATING)
			{
				pthread_mutex_lock(philo->write);
				set_status(philo + i, DEAD);
				printf("monitor: philo #%i:\nlastmeal = %llu\ntmsp = %llu\ndifference = %llu\n", i + 1,
						 get_lastmeal(philo + i), gettime(), gettime() - get_lastmeal(philo + i));
				cs = DEAD;
				printf("%llu %d is died\n", gettime() - tmp, i + 1);
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
