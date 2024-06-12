#include "philo.h"

static int	init_stats(t_stats *stats, char **argv)
{
	stats->philo_num = ft_atoi(argv[1]);
	stats->ttd = ft_atoi(argv[2]);
	stats->tte = ft_atoi(argv[3]);
	stats->tts = ft_atoi(argv[4]);
	stats->eat_limit = 0;
	printf("ttd = %ld\ntte = %ld\ntts = %ld\n", stats->ttd, stats->tte, stats->tts);
	return (0);
}

t_philo	*init_philo(char **argv)
{
	int	i;
	int	num;
	t_philo	*philo;
	t_stats *st;
	pthread_mutex_t *forks;

	i = -1;
	num = ft_atoi(argv[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	st = (t_stats *)malloc(sizeof(t_stats));
	if (!philo || !forks || !st)
		return (NULL);
	init_stats(st, argv);
	while (i < num)
	{
		pthread_mutex_init(forks + i, NULL);
		philo[i].eat_count = 0;
		philo[i].index = i + 1;
		philo[i].status = 0;
		philo[i].stats = st;
		if (i + 1 == num)
		{
			philo[i].left = &forks[i];
			philo[i].right = &forks[0];
			break ;
		}
		else
			philo[i].left = &forks[i + 1];
		philo[i].right = &forks[i];
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

	th = (pthread_t *)malloc(sizeof(pthread_t) * philo->stats->philo_num);
	if (!th)
		return ;
	while (++i < philo->stats->philo_num)
	{
		if(pthread_create(th + i, NULL, start_routine, philo + i))
			return ;
	}
	i = -1;
	while (++i < philo->stats->philo_num)
	{
		pthread_join(th[i], &status);
	}
}

void	*start_routine(void *arg)
{
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		if (try_eat(philo))
			break ;
		print_action(SLEEP, philo->index, philo->stats);
		print_action(THINK, philo->index, philo->stats);
	}
	return (NULL);
}

int	try_eat(t_philo *philo)
{
	struct timeval	end;
	struct timeval	start;

	gettimeofday(&start, NULL);
	pthread_mutex_lock(philo->left);
	gettimeofday(&end, NULL);
	if (cmp_time(start, end, philo->stats->ttd))
	{
		pthread_mutex_unlock(philo->left);
		print_action(DEAD, philo->index, philo->stats);
		return (1);
	}
	print_action(FORK, philo->index, philo->stats);
	pthread_mutex_lock(philo->right);
	gettimeofday(&end, NULL);
	if (cmp_time(start, end, philo->stats->ttd))
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		print_action(DEAD, philo->index, philo->stats);
		return (1);
	}
	print_action(FORK, philo->index, philo->stats);
	print_action(EATING, philo->index, philo->stats);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

int cmp_time(struct timeval start, struct timeval end, suseconds_t limit)
{
	printf("result = %ld limit = %ld\n", ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000), limit);
	return (limit < ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000));
}

void	print_action(int status, int index, const t_stats *stats)
{
	struct timeval t;
	
	gettimeofday(&t, NULL);
	if (DEAD == status)
		printf("%ld %d ++++++++++++++++DIE++++++++++++++++\n", IN_MILISEC(t.tv_usec), index);
	else if (EATING == status)
	{
		printf("%ld %d is eating\n", IN_MILISEC(t.tv_usec), index);
		usleep(IN_MICROSEC(stats->tte));
	}
	else if (SLEEP == status)
	{
		printf("%ld %d is sleep\n", IN_MILISEC(t.tv_usec), index);
		usleep(IN_MICROSEC(stats->tts));
	}
	else if (FORK == status)
		printf("%ld %d has taken a fork\n", IN_MILISEC(t.tv_usec), index);
	else if (THINK == status)
		printf("%ld %d is thinking\n", IN_MILISEC(t.tv_usec), index);
}