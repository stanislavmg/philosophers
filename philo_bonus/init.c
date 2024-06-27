#include "philo_bonus.h"

static t_stats	*init_stats(char **argv)
{
	t_stats	*stats;

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
	return (stats);
}

static t_philo	*init_philo(t_stats *st)
{
	int		i;
	t_philo	*philo;
	
	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * st->philo_num);
	if (!philo)
		return (NULL);
	while (++i < st->philo_num)
	{
		philo[i].eat_count = 0;
		philo[i].index = i + 1;
		philo[i].status = THINK;
		philo[i].stats = st;
		philo[i].forks = 0;
	}
	return (philo);
}

int	init(char **argv, t_philo **philo)
{
	t_stats	*st;

	st = NULL;
	st = init_stats(argv);
	if (!st)
		return (1);
	*philo = init_philo(st);
	if (!philo)
		return (1);
	return (0);
}
