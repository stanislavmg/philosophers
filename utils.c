#include "philo.h"

int valid_args(int argc, char **argv)
{
	int i;
	int j;
	int count;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("To many arguments\n", STDERR_FILENO);
		return (1);
	}
	while (argv[++i])
	{
		j = 0;
		count = 0;
		while ((argv[i][j] >= '\t' && argv[i][j] <= '\r') || argv[i][j] == ' ')
			j++;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while ('0' == argv[i][j])
			j++;
		while (*argv[i] && (argv[i][j] >= '0' && argv[i][j] <= '9'))
		{
			j++;
			count++;
		}
		while (argv[i][j] && ((argv[i][j] >= '\t' && argv[i][j] <= '\r') || argv[i][j] == ' '))
			j++;
		if (argv[i][j] || count > 10 || 0 == count)
			return (1);
	}
	return (0);
}

// int	check_stats(t_stats *stats)
// {
// 	if (stats->eat_limit < 0 ||
// 		stats->ttd < 0 ||
// 		stats->tte < 0 ||
// 		stats->tts < 0)
// 		return (1);
// 	return (0);
// }

void free_philo(t_philo *philo, pthread_mutex_t *forks, pthread_t *th)
{
	int i;

	i = -1;
	while (++i < philo->stats->philo_num)
		pthread_mutex_destroy(forks + i);
	free(forks);
	free(th);
	free((void *)philo->stats);
	free(philo);
}