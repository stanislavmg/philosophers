#include "philo.h"
static void	print_action(int status, const t_philo *philo)
{
	long	t;

	t = gettime();
	if (DEAD == status)
		printf("%ld %d died\n", t - philo->timestamp, philo->index);
	else if (EATING == status)
		printf("%ld %d is eating\n", t - philo->timestamp, philo->index);
	else if (SLEEP == status)
		printf("%ld %d is sleep\n", t - philo->timestamp, philo->index);
	else if (FORK == status)
		printf("%ld %d has taken a fork\n", t - philo->timestamp, philo->index);
	else if (THINK == status)
		printf("%ld %d is thinking\n", t - philo->timestamp, philo->index);
	else
		printf("Error: unexpected status\n");
}


static int	handle_status(int status, t_philo *philo)
{
	int		cur_status;

	cur_status = get_status(philo);
	if (STOP == cur_status || DEAD == cur_status || FULL == cur_status)
		return (1);
	print_action(status, philo);
	if (DEAD == status)
		set_status(philo, status);
	else if (SLEEP == status)
		ft_usleep(philo->stats->tts);
	else if (EATING == status)
	{
		philo->eat_count++;
		philo->lastmeal = gettime();
		ft_usleep(philo->stats->tte);
	}
	return (0);
}

static void    *handle_one(t_philo *philo)
{
    pthread_mutex_lock(philo->left);
	handle_status(FORK, philo);
    ft_usleep(philo->stats->ttd);
	handle_status(DEAD, philo);
    pthread_mutex_unlock(philo->left);
	return (NULL);
}

static int	cmp_time(const t_philo *philo)
{
	return (philo->stats->ttd < (gettime() - philo->lastmeal));
}

static int	try_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (cmp_time(philo))
	{
		pthread_mutex_unlock(philo->left);
		handle_status(DEAD, philo);
		return (1);
	}
	handle_status(FORK, philo);
	pthread_mutex_lock(philo->right);
	if (cmp_time(philo))
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		handle_status(DEAD, philo);
		return (1);
	}
	handle_status(FORK, philo);
	handle_status(EATING, philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;
	int 	cur_status;

	philo = (t_philo *)arg;
	if (philo->stats->philo_num == 1)
		return (handle_one(philo));
	if (philo->index % 2 == 0)
		ft_usleep(philo->stats->tte);
	cur_status = 0;
	while (cur_status != DEAD && cur_status != FULL && cur_status != STOP)
	{
		if (cmp_time(philo))
			handle_status(DEAD, philo);
		try_eat(philo);
		if (philo->eat_count >= philo->stats->eat_limit
			&& philo->stats->eat_limit != UNDEFINED)
			set_status(philo, FULL);
		handle_status(SLEEP, philo);
		handle_status(THINK, philo);
		cur_status = get_status(philo);
	}
	return (NULL);
}

