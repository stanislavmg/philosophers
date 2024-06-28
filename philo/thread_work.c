#include "philo.h"

static int	print_action(int status, t_philo *philo)
{
	long	t;

	t = gettime();
	if (STOP == philo->status)
		return (1);
	else if (DEAD == status)
	{
		printf("%ld %d died\n", t - philo->timestamp, philo->index);
		philo->status = status;
		return (1);
	}
	else if (EATING == status)
	{
		printf("%ld %d is eating\n", t - philo->timestamp, philo->index);
		philo->eat_count++;
		philo->lastmeal = t;
		ft_usleep(philo->stats->tte);
	}
	else if (SLEEP == status)
	{
		printf("%ld %d is sleep\n", t - philo->timestamp, philo->index);
		ft_usleep(philo->stats->tts);
	}
	else if (FORK == status)
		printf("%ld %d has taken a fork\n", t - philo->timestamp, philo->index);
	else if (THINK == status)
		printf("%ld %d is thinking\n", t - philo->timestamp, philo->index);
	else
		printf("Error: unexpected status\n");
	return (0);
}

static int	cmp_time(t_philo *philo)
{
	return (philo->stats->ttd < (gettime() - philo->lastmeal));
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
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		ft_usleep(philo->stats->tte);
	while (1)
	{
		if (cmp_time(philo))
			philo->status = DEAD;
		if (philo->status == DEAD)
		{
			print_action(DEAD, philo);
			break ;
		}
		if (STOP == philo->status || try_eat(philo))
			break ;
		if (philo->eat_count >= philo->stats->eat_limit
			&& philo->stats->eat_limit != UNDEFINED)
		{
			philo->status = FULL;
			break ;
		}
		if (print_action(SLEEP, philo))
			break ;
		if (print_action(THINK, philo))
			break ;
	}
	return (NULL);
}

void    *handle_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
    pthread_mutex_lock(philo->left);
	print_action(FORK, philo);
    ft_usleep(philo->stats->ttd);
	print_action(DEAD, philo);
    pthread_mutex_unlock(philo->left);
    return (NULL);
}