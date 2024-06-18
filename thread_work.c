#include "philo.h"
static void	print_action(int status, t_philo *philo)
{
	struct timeval t;
	
	gettimeofday(&t, NULL);
	if (*philo->exp)
		return ;
	if (DEAD == status)
	{
		//pthread_mutex_lock(philo->lock);
		printf("%ld %d died\n", philo->timestamp, philo->index);
		philo->status = DEAD;
		//pthread_mutex_unlock(philo->lock);
	}
	else if (EATING == status)
	{
		printf("%ld %d is eating\n", philo->timestamp, philo->index);
		philo->eat_count++;
		usleep(IN_MICROSEC(philo->stats->tte));
		philo->timestamp += philo->stats->tte;
	}
	else if (SLEEP == status)
	{
		printf("%ld %d is sleep\n", philo->timestamp, philo->index);
		usleep(IN_MICROSEC(philo->stats->tts));
		philo->timestamp += philo->stats->tts;
	}
	else if (FORK == status)
	{
		printf("%ld %d has taken a fork\n", philo->timestamp, philo->index);
	}
	else if (THINK == status)
	{
		printf("%ld %d is thinking\n", philo->timestamp, philo->index);
	}
}

static int cmp_time(struct timeval *start, struct timeval *end, suseconds_t *limit)
{
	return (*limit <= ((end->tv_sec - start->tv_sec) * 1000 + (end->tv_usec - start->tv_usec) / 1000));
}

static int	try_eat(t_philo *philo, struct timeval *start)
{
	struct timeval	end;

	printf("Philosopher #%d try to get fork\n", philo->index);
	pthread_mutex_lock(philo->left);
	gettimeofday(&end, NULL);
	if (cmp_time(start, &end, &philo->stats->ttd))
	{
		pthread_mutex_unlock(philo->left);
		print_action(DEAD, philo);
		return (1);
	}
	philo->timestamp += ((end.tv_sec - start->tv_sec) * 1000 + (end.tv_usec - start->tv_usec) / 1000);
	print_action(FORK, philo);
	pthread_mutex_lock(philo->right);
	gettimeofday(&end, NULL);
	if (cmp_time(start, &end, &philo->stats->ttd))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		print_action(DEAD, philo);
		return (1);
	}
	philo->timestamp += ((end.tv_sec - start->tv_sec) * 1000 + (end.tv_usec - start->tv_usec) / 1000);
	print_action(FORK, philo);
	print_action(EATING, philo);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;
	struct timeval	end;
	struct timeval	start;

	philo = (t_philo *)arg;
	//pthread_mutex_lock(philo->lock);
	gettimeofday(&start, NULL);
	//pthread_mutex_unlock(philo->lock);
	while (1)
	{
		gettimeofday(&end, NULL);
		pthread_mutex_lock(philo->lock);
		if (cmp_time(&start, &end, &philo->stats->ttd))
			philo->status = DEAD;
		if (philo->status == DEAD)
		{
			printf("Philosopher #%d is over woriking\n", philo->index);
			pthread_mutex_unlock(philo->lock);
			break ;
		}
		pthread_mutex_unlock(philo->lock);
		if (try_eat(philo, &start))
		{
			printf("Philosopher #%d is over woriking\n", philo->index);
			break ;
		}
		gettimeofday(&start, NULL);
		print_action(SLEEP, philo);
		print_action(THINK, philo);
	}
	return (NULL);
}
