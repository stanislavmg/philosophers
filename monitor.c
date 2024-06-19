#include "philo.h"
static void	sync_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->stats->philo_num)
		pthread_mutex_lock(philo[i].lock);
	usleep(IN_MICROSEC(1000));
	i = -1;
	while (++i < philo->stats->philo_num)
	{
		philo[i].timestamp = gettime(1);
		philo[i].lastmeal = philo[i].timestamp;
		pthread_mutex_unlock(philo[i].lock);
	}
}

int seek_min(t_philo *philo)
{
	t_philo *rval;
	int min;
	int i;

	i = 0;
	min = philo[i].eat_count;
	rval = philo;
	while (i < philo->stats->philo_num)
	{
		if (philo[i].eat_count < min)
		{
			min = philo[i].eat_count;
			rval = philo + i;
		}
		i++;
	}
	return (rval->index - 1);
}

void	*monitoring(void *arg)
{
	int	i;
	int index;
	int left;
	int right;
	//int c_status;
	t_philo *philo;

	
	philo = (t_philo *)arg;
	sync_threads(philo);
	while (1)
	{
		i = 0;
		while (i < philo->stats->philo_num)
		{
			if (philo[i].status == DEAD)
			{
				pthread_mutex_lock(philo->lock_write);
				printf("Monitor message: Philosopher #%d dead\n", philo[i].index);
				i = 0;
				while (i < philo->stats->philo_num)
				{
					pthread_mutex_lock(philo[i].lock);
					philo[i].status = DEAD;
					pthread_mutex_unlock(philo[i].lock);
					i++;
				}
				pthread_mutex_unlock(philo->lock_write);
				return (NULL);
			}
			i++;
		}
		index = seek_min(philo);
		if (index == philo->stats->philo_num - 1)
		{
			left = index - 1;
			right = 0;
		}
		else if (index == 0)
		{
			left = philo->stats->philo_num - 1;
			right = index + 1;
		}
		else{
			left = index - 1;
			right = index + 1;
		}
		pthread_mutex_lock(philo[right].lock);
		pthread_mutex_lock(philo[left].lock);
		//c_status = philo[index].status;
		//while(philo[index].status == c_status);
		usleep(IN_MICROSEC(10));
		pthread_mutex_unlock(philo[right].lock);
		pthread_mutex_unlock(philo[left].lock);
		(void)left;
	//	printf("Hello from Monitor\n");
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