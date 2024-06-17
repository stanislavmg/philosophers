#include "philo.h"
static void	print_action(int status, t_philo *philo)
{
	struct timeval t;
	
	gettimeofday(&t, NULL);
	if (DEAD == status)
	{
		pthread_mutex_lock(philo->lock);
		printf("%ld %d ++++++++++++++++DIE++++++++++++++++\n", IN_MILISEC(t.tv_usec), philo->index);
		philo->status = DEAD;
		pthread_mutex_unlock(philo->lock);
	}
	else if (EATING == status)
	{
		printf("%ld %d is eating\n", IN_MILISEC(t.tv_usec), philo->index);
		pthread_mutex_lock(philo->lock);
		philo->eat_count++;
		pthread_mutex_unlock(philo->lock);
		usleep(IN_MICROSEC(philo->stats->tte));
	}
	else if (SLEEP == status)
	{
		printf("%ld %d is sleep\n", IN_MILISEC(t.tv_usec), philo->index);
		usleep(IN_MICROSEC(philo->stats->tts));
	}
	else if (FORK == status)
		printf("%ld %d has taken a fork\n", IN_MILISEC(t.tv_usec), philo->index);
	else if (THINK == status)
		printf("%ld %d is thinking\n", IN_MILISEC(t.tv_usec), philo->index);
}

static int cmp_time(struct timeval start, struct timeval end, const suseconds_t *limit)
{
	//printf("result = %ld limit = %ld\n", ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000), limit);
	return (*limit < ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000));
}

static int	try_eat(t_philo *philo)
{
	struct timeval	end;
	struct timeval	start;

	gettimeofday(&start, NULL);
	pthread_mutex_lock(philo->left);
	gettimeofday(&end, NULL);
	if (cmp_time(start, end, &philo->stats->ttd))
	{
		pthread_mutex_unlock(philo->left);
		print_action(DEAD, philo);
		return (1);
	}
	print_action(FORK, philo);
	pthread_mutex_lock(philo->right);
	gettimeofday(&end, NULL);
	if (cmp_time(start, end, &philo->stats->ttd))
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
	while (1)
	{
		pthread_mutex_lock(philo->lock);
		if (try_eat(philo))
			break ;
		pthread_mutex_unlock(philo->lock);
		print_action(SLEEP, philo);
		print_action(THINK, philo);
	}
	return (NULL);
}
