#include "philo.h"

static t_stats	*init_stats(char **argv, int *err)
{
	t_stats	*stats;

	stats = (t_stats *)malloc(sizeof(t_stats));
	if (!stats)
	{
		*err = ERR_MALLOC;
		return (NULL);
	}
	stats->philo_num = ft_atoi(argv[1]);
	stats->ttd = ft_atoi(argv[2]);
	stats->tte = ft_atoi(argv[3]);
	stats->tts = ft_atoi(argv[4]);
	if (argv[5])
		stats->eat_limit = ft_atoi(argv[5]);
	if (check_stats(stats))
	{
		*err = ERR_STATS;
		return (NULL);
	}
	if (!argv[5])
		stats->eat_limit = UNDEFINED;
	return (stats);
}

static pthread_mutex_t	*forks_init(int num, int *err)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!forks)
	{
		*err = ERR_MALLOC;
		return (NULL);
	}
	while (i < num)
	{
		if (pthread_mutex_init(forks + i, NULL))
		{
			*err = ERR_MUTEX;
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static t_philo	*init_philo(t_stats *st, pthread_mutex_t *forks, int *err)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * st->philo_num);
	if (!philo)
	{
		*err = ERR_MALLOC;
		return (NULL);
	}
	while (++i < st->philo_num)
	{
		philo[i].eat_count = 0;
		philo[i].index = i + 1;
		philo[i].status = THINK;
		philo[i].stats = st;
		philo[i].left = &forks[i];
		philo[i].right = &forks[(i + 1) % st->philo_num];
	}
	return (philo);
}

t_philo	*init(char **argv, pthread_mutex_t **forks, int *err)
{
	t_stats	*st;
	t_philo *philo;

	philo = NULL;
	st = NULL;
	st = init_stats(argv, err);
	if (!st)
		return (NULL);
	*forks = forks_init(st->philo_num, err);
	if (!forks)
		return (NULL);
	if (st->philo_num)
		philo = init_philo(st, *forks, err);
	if (!philo)
		return (NULL);
	return (philo);
}

int	create_threads(t_philo *philo, pthread_t *th)
{
	int			i;
	void		*status;

	i = 0;

	if (pthread_create(th + i, NULL, monitoring, philo))
		return (ERR_THREAD);
	usleep(1e3);
	philo->timestamp = gettime();
	while (++i < philo->stats->philo_num + 1)
	{
		philo[i - 1].lastmeal = philo->timestamp;
		philo[i - 1].timestamp = philo->timestamp;
		if (philo->stats->philo_num > 1)
		{
			if (pthread_create(th + i, NULL, start_routine, philo + i - 1))
				return (ERR_THREAD);
		}
		else
		{
			if (pthread_create(th + i, NULL, handle_one, philo + i - 1))
				return (ERR_THREAD);
		}
	}
	pthread_join(th[0], &status);
	i = 0;
	while (++i < philo->stats->philo_num + 1)
	 	pthread_join(th[i], &status);
	return (0);
}
