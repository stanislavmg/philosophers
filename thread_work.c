#include "philo.h"

static void	print_action(int status, t_philo *philo)
{
	//pthread_mutex_lock(philo->lock_write);
	if (STOP == philo->status)
	{
		pthread_mutex_unlock(philo->lock_write);
		return ;
	}
	else if (DEAD == status)
	{
		printf("%ld %d died\n", gettime(1) - philo->timestamp, philo->index);
		philo->status = DEAD;
	}
	else if (EATING == status)
	{
		printf("%ld %d is eating\n", gettime(1) - philo->timestamp, philo->index);
		pthread_mutex_unlock(philo->lock_write);
		philo->eat_count++;
		philo->status = EATING;
		philo->lastmeal = gettime(1);
		ft_usleep(philo->stats->tte);
		return ;
	}
	else if (SLEEP == status)
	{
		printf("%ld %d is sleep\n", gettime(1) - philo->timestamp, philo->index);
		pthread_mutex_unlock(philo->lock_write);
		philo->status = SLEEP;
		ft_usleep(philo->stats->tts);
		return ;
	}
	else if (FORK == status)
		printf("%ld %d has taken a fork\n", gettime(1) - philo->timestamp, philo->index);
	else if (THINK == status)
		printf("%ld %d is thinking\n", gettime(1) - philo->timestamp, philo->index);
	//pthread_mutex_unlock(philo->lock_write);
}

static int cmp_time(t_philo * philo)
{
	return (philo->stats->ttd <= (gettime(1) - philo->lastmeal));
}

static int	try_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (cmp_time(philo))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->lock);
		print_action(DEAD, philo);
		return (1);
	}
	print_action(FORK, philo);
	pthread_mutex_lock(philo->right);
	if (cmp_time(philo))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		print_action(DEAD, philo);
		return (1);
	}
	print_action(FORK, philo);
	print_action(EATING, philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->lock);
	pthread_mutex_unlock(philo->lock);
	philo->timestamp = gettime(1);
	philo->lastmeal = philo->timestamp;
	if (philo->index % 2 == 0)
		ft_usleep(philo->stats->tte);
	while (1)
	{
		if (philo->index % 2 == 0)
		 	ft_usleep(1);
		if (cmp_time(philo))
			philo->status = DEAD;
		pthread_mutex_lock(philo->lock);
		if (philo->status == DEAD)
		{
			print_action(DEAD, philo);
			break ;
		}
		pthread_mutex_unlock(philo->lock);
		if (STOP ==  philo->status || try_eat(philo))
			break ;
		print_action(SLEEP, philo);
		print_action(THINK, philo);
	}
	pthread_mutex_unlock(philo->lock);
	return (NULL);
}
