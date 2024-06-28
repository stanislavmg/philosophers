#include "philo.h"

static int	check_str(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		if ('0' == s[i] && s[i + 1])
		{
			i++;
			continue;
		}
		i++;
		count++;
	}
	while (s[i] && ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' '))
		i++;
	if (s[i] || count > 10 || 0 == count)
		return (1);
	return (0);
}

int	valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
		return (1);
	while (argv[++i])
	{
		if (check_str(argv[i]))
			return (1);
	}
	return (0);
}

int	check_stats(t_stats *stats)
{
	if (stats->eat_limit < 0 ||
		stats->ttd < 0 ||
		stats->tte < 0 ||
		stats->tts < 0 ||
		stats->philo_num < 0)
		return (1);
	return (0);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void	free_philo(t_philo *philo, pthread_mutex_t *forks, pthread_t *th)
{
	int	i;

	i = -1;
	while (++i < philo->stats->philo_num)
		pthread_mutex_destroy(forks + i);
	free(forks);
	free(th);
	free(philo->stats);
	free(philo);
}

void	ft_usleep(long sleep_time)
{
	long	start;

	start = gettime();
	while ((gettime() - start) < sleep_time)
		usleep(500);
}
