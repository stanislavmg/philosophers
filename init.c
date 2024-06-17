#include "philo.h"

static t_stats	*init_stats(char **argv)
{
	t_stats 		*stats;

	stats = (t_stats *)malloc(sizeof(t_stats));
	if (!stats)
		return (NULL);
	stats->philo_num = ft_atoi(argv[1]);
	stats->ttd = ft_atoi(argv[2]);
	stats->tte = ft_atoi(argv[3]);
	stats->tts = ft_atoi(argv[4]);
	if (argv[5])
		stats->eat_limit = ft_atoi(argv[5]);
	else
		stats->eat_limit = UNDEFINED;
	// if (check_stats(stats))
	// {
	// 	free(stats);
	// 	return (NULL);
	// }
	return (stats);
}

static pthread_mutex_t	*forks_init(int num)
{
	pthread_mutex_t *forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!forks)
		return (NULL);
	while (i < num)
	{
		if(pthread_mutex_init(forks + i, NULL))
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static t_philo	*init_philo(t_stats *st, pthread_mutex_t *forks)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * st->philo_num);
	if (!philo)
		return (NULL);
	while (i < st->philo_num)
	{
		philo[i].eat_count = 0;
		philo[i].index = i + 1;
		philo[i].status = 0;
		philo[i].stats = st;
		if ((i + 1) % 2 == 0)
		{
			philo[i].left = &forks[i];
			philo[i].right = &forks[i + 1];
		}
		else if (i + 1 == st->philo_num)
		{
			philo[i].left = &forks[0];
			philo[i].right = &forks[i];
		}
		else
		{
			philo[i].left = &forks[i + 1];
			philo[i].right = &forks[i];
		}
		i++;
	}
	return (philo);	
}

int	init(char **argv, t_philo **philo, pthread_mutex_t *forks)
{
	t_stats 		*st;

	st = NULL;
	st = init_stats(argv);
	if (!st)
		return (ERR_STATS);
	forks = forks_init(st->philo_num);
	if (!forks)
		return (ERR_MUTEX);
	*philo = init_philo(st, forks);
	if (!philo)
		return (ERR_MALLOC);
	return (0);
}

int create_threads(t_philo *philo, pthread_mutex_t *forks)
{
	int			i;
	void 		*status;
	pthread_t	*th;

	i = 0;
	th = (pthread_t *)malloc(sizeof(pthread_t) * philo->stats->philo_num + 1);
	if (!th)
		return (ERR_MALLOC);
	if(pthread_create(th + i, NULL, monitoring, philo + i))
		return (ERR_THREAD);
	while (++i < philo->stats->philo_num)
	{
		if(pthread_create(th + i, NULL, start_routine, philo + i))
			return (ERR_THREAD);
		if (pthread_detach(th[i]))
			return (ERR_THREAD);
	}
	pthread_join(th[0], &status);
	if (!status)
		exit(1); //TODO
	free_philo(philo, forks, th);
	return (0);
}

// void	stop_working(t_philo *philo, pthread_mutex_t *forks, pthread_t *th)
// {
// 	free_philo(philo, forks, th);
// }