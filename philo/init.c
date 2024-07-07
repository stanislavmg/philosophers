#include "philo.h"

t_data	*init(int argc, char **argv)
{
	t_data *data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->stats = init_stats(argc, argv);
	if (!data->stats)
		return (free_data(data));
	if (init_mutex(data, data->stats->philo_num))
		return (data);
	data->all_philo = init_philo(data, data->stats->philo_num);
	if (!data->all_philo)
		return (data);
	data->threads = (pthread_t *)malloc(sizeof(pthread_t) * (data->stats->philo_num + 1));
	if (!data->threads)
		return (data);
	if (init_threads(data->threads, data->all_philo, data->stats->philo_num))
		return (data);
	return (data);
}

t_stats	*init_stats(int argc, char **argv)
{
	t_stats	*stats;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect arguments\n");
		return (NULL);
	}
	stats = (t_stats *)ft_calloc(1, sizeof(t_stats));
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
	if (check_stats(stats))
	{
		free(stats);
		return (NULL);
	}
	return (stats);
}

int init_mutex(t_data *data, int num)
{
	int				i;

	i = 0;
	// one time malloc for all mutexes
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num * 2);
	if (!data->forks)
		return (1);
	data->locks = data->forks + num;
	while (i < num)
	{
		if (pthread_mutex_init(data->forks + i, NULL) ||
			pthread_mutex_init(data->locks + i, NULL))
			return (1);
		i++;
	}
	return (0);
}

t_philo	*init_philo(t_data *data, int num)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t *t;

	i = -1;
	philo = (t_philo *)ft_calloc(num, sizeof(t_philo));
	if (!philo)
		return (NULL);
	while (++i < num)
	{
		philo[i].lock = data->locks + i;
		philo[i].index = i + 1;
		philo[i].stats = data->stats;
		philo[i].left = &data->forks[i];
		philo[i].right = &data->forks[(i + 1) % num];
	}
	// swap the last philosopher's forks to prevent a deadlock
	t = philo[i - 1].right;
	philo[i - 1].right = philo[i - 1].left;
	philo[i - 1].left = t;
	return (philo);
}

int	init_threads(pthread_t *th, t_philo *philo, int n)
{
	int			i;

	i = -1;
	if (pthread_create(th, NULL, monitoring, philo))
		return (1);
	usleep(1e3);
	philo->timestamp = gettime();
	while (++i < n)
	{
		philo[i].lastmeal = philo->timestamp;
		philo[i].timestamp = philo->timestamp;
		if (pthread_create(++th, NULL, start_routine, philo + i))
			return (1);
	}
	return (0);
}
