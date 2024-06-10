#include "philo.h"

static int	init_stats(t_stats *stats, char **argv)
{
	stats->philo_num = ft_atoi(argv[1]);
	stats->ttd = ft_atoi(argv[2]);
	stats->tte = ft_atoi(argv[3]);
	stats->tts = ft_atoi(argv[4]);
	return (0);
}

t_philo	*init_philo(char **argv)
{
	int	i;
	int	num;
	t_philo	*philo;
	pthread_mutex_t *forks;

	i = -1;
	num = ft_atoi(argv[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!philo || !forks)
		return (NULL);
	init_stats(&philo->stats, argv);
	while (i < philo->stats.philo_num)
	{
		philo[i].eat_count = 0;
		philo[i].index = i + 1;
		if (!i)
			philo[i].left = &forks[num - 1];
		else
			philo[i].left = &forks[i - 1];
		philo[i].right = &forks[i];
		philo[i].status = 0;
		i++;
	}
	return (philo);
}

void create_threads(t_philo *philo)
{
	int	i;
	void *status;
	pthread_t	*th;

	i = -1;

	th = (pthread_t *)malloc(sizeof(pthread_t) * philo->stats.philo_num);
	if (!th)
		return ;
	while (++i < philo->stats.philo_num)
	{
		if(pthread_create(th + i, NULL, start_routine, philo + i))
			return ;
	}
	i = -1;
	while (++i < philo->stats.philo_num)
	{
		pthread_join(th[i], &status);
		if (!status)
			exit(EXIT_FAILURE);
	}
}

void	*start_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	start;
	struct timeval	end;
	
	philo = (t_philo *)arg;
	while (1)
	{
		philo->status = e_think;
		gettimeofday(&start, NULL);
		gettimeofday(&end, NULL);
		print_action(philo, start.tv_usec);
		if ((end.tv_usec - start.tv_usec) > philo->stats.ttd)
		{
			philo->status = e_dead;
			print_action(philo, end.tv_usec);
			break ;
		}
		if (try_eat(philo))
			continue ;
		gettimeofday(&start, NULL);
		print_action(philo, start.tv_usec);
		usleep(philo->stats.tts);
	}
	return (NULL);
}

int	try_eat(t_philo *philo)
{
	struct timeval start;
	
	if (philo->index == 1)
	{
		if (pthread_mutex_lock(philo->right))
			return (1);	
		if (pthread_mutex_lock(philo->left))
		{
			pthread_mutex_unlock(philo->right);
			return (1);
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->left))
			return (1);
		if (pthread_mutex_lock(philo->right))
		{
			pthread_mutex_unlock(philo->left);
			return (1);
		}
	}
	gettimeofday(&start, NULL);
	philo->status = e_fork;
	print_action(philo, start.tv_usec);
	gettimeofday(&start, NULL);
	print_action(philo, start.tv_usec);
	philo->status = e_eating;
	gettimeofday(&start, NULL);
	print_action(philo, start.tv_usec);
	usleep(philo->stats.tte);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	philo->status = e_sleep;
	return (0);
}

void	print_action(t_philo *philo, size_t time)
{
	if (e_dead == philo->status)
	{
		printf("%lu %d die\n", time, philo->index);
	}
	else if (e_eating == philo->status)
	{
		printf("%lu %d is eating\n", time, philo->index);
		usleep(philo->stats.tte);
	}
	else if (e_sleep == philo->status)
	{
		printf("%lu %d is sleep\n", time, philo->index);
		usleep(philo->stats.tts);
	}
	else if (e_fork == philo->status)
	{
		printf("%lu %d has taken a fork\n", time, philo->index);
	}
	else if (e_think == philo->status)
	{
		printf("%lu %d is thinking\n", time, philo->index);
	}
}