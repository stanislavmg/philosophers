#include "philo.h"

static void	print_action(int status, t_philo *philo)
{
	long t;

	t = gettime(1);
	philo->status = status;
	pthread_mutex_lock(philo->lock_write);
	pthread_mutex_lock(philo->lock);
	if (STOP == philo->status)
	{
		pthread_mutex_unlock(philo->lock);
		pthread_mutex_unlock(philo->lock_write);
		return ;
	}
	else if (DEAD == philo->status)
	{
		printf("%ld %d died\n", t - philo->timestamp, philo->index);
		printf("difference = %ld\n", t - philo->lastmeal);
	}
	else if (EATING == philo->status)
	{
		printf("%ld %d is eating\n", t - philo->timestamp, philo->index);
		philo->eat_count++;
		philo->lastmeal = t;
		ft_usleep(philo->stats->tte);
	}
	else if (SLEEP == philo->status)
	{
		printf("%ld %d is sleep\n", t - philo->timestamp, philo->index);
		ft_usleep(philo->stats->tts);
	}
	else if (FORK == philo->status)
		printf("%ld %d has taken a fork\n", t - philo->timestamp, philo->index);
	else if (THINK == philo->status)
		printf("%ld %d is thinking\n", t - philo->timestamp, philo->index);
	else
		printf("Error: unexpected status\n");
	pthread_mutex_unlock(philo->lock_write);
	pthread_mutex_unlock(philo->lock);
}

static int cmp_time(t_philo * philo)
{
	return (philo->stats->ttd < (gettime(1) - philo->lastmeal));
}

static int	try_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (cmp_time(philo))
	{
		pthread_mutex_unlock(philo->left);
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
	while (1)
	{
		if (philo->eat_count >= philo->stats->eat_limit
			&& philo->stats->eat_limit != UNDEFINED)
		{
			printf("BYE\n");
			philo->status = FULL;
			break ;
		}
		if (cmp_time(philo))
			philo->status = DEAD;
		if (philo->status == DEAD)
		{
			print_action(DEAD, philo);
			break ;
		}
		if (STOP ==  philo->status || try_eat(philo))
			break ;
		print_action(SLEEP, philo);
		print_action(THINK, philo);
	}
	return (NULL);
}
