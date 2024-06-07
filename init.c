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
	pthread_mutex_t *fork;

	i = -1;
	num = ft_atoi(argv[i]);
	philo = (t_philo *)malloc(sizeof(t_philo) * num);
	fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!philo || !fork)
		return (NULL);
	init_stats(&philo->stats, argv);
	while (++i < philo->stats.philo_num)
	{
		philo[i].eat_count = 0;
		philo[i].index = i;
		if (!i)
			philo[i].left = &fork[num - 1];
		else
			philo[i].left = &fork[i - 1];
		philo[i].right = &fork[i];
		philo[i].status = 0;
	}
	return (philo);
}

void create_threads(t_philo *philo)
{
	int	i;
	pthread_t	*th;
	pthread_mutex_t *mt;

	i = -1;
	th = (pthread_t *)malloc(sizeof(pthread_t) * philo->stats.philo_num);
	if (!th || !mt)
		return ;
	while (++i < philo->stats.philo_num)
	{
		if(pthread_create(th + i, NULL, start_routine, philo + i))
			return ;
	}
	i = -1;
	while (++i < philo->stats.philo_num)
		pthread_join(th + i, NULL);
}

void	*start_routine(t_philo *philo)
{
	while (philo->status != DIE)
	{
		if ()
	}
	return (NULL);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	philo->status = FORK;
	print_action(philo, );
	pthread_mutex_lock(philo->right);

}

int	check_neighbour(t_philo *philo)
{

	return (0);
}

void	print_action(t_philo *philo, time_t time)
{
	if (DIE == philo->status)
	{
		printf("%d %d died\n", (int)time, philo->index);
		interrupt_philo();// TODO
	}
	else if (EATING == philo->status)
	{
		printf("%d %d is eating\n", (int)time, philo->index);
		usleep(philo->stats.tte);
	}
	else if (SLEEPING == philo->status)
	{
		printf("%d %d is sleeping\n", (int)time, philo->index);
		usleep(philo->stats.tts);
	}
	else if (FORK == philo->status)
	{
		printf("%d %d has taken a fork\n", (int)time, philo->index);
	}
	else if (THINKING == philo->status)
	{
		printf("%d %d is thinking\n", (int)time, philo->index);
		
	}

}