#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*pt;
	size_t	i;
	size_t	n;

	i = 0;
	n = size * nmemb;
	pt = (char *)malloc(n);
	if (!pt)
		return (NULL);
	while (i < n)
		pt[i++] = 0;
	return ((void *)pt);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void	*free_data(t_data *data)
{
	int	i;

	i = -1;
	if (!data)
		return (NULL);
	if (data->stats)
	{
	while (++i < data->stats->philo_num)
	{
		pthread_mutex_destroy(data->locks + i);
		pthread_mutex_destroy(data->forks + i);
	}
	}
	free(data->forks);
	free(data->threads);
	free(data->stats);
	free(data->all_philo);
	free(data);
	return (NULL);
}

void	ft_usleep(long sleep_time)
{
	long	start;

	start = gettime();
	while ((gettime() - start) < sleep_time)
		usleep(250);
}

int	check_stats(t_stats *stats)
{
	if (stats->ttd < 0 ||
		stats->tte < 0 ||
		stats->tts < 0 ||
		stats->philo_num < 0 ||
		(stats->eat_limit < 0 && stats->eat_limit != UNDEFINED))
	{
		printf("Incorrect arguments\n");
		return (1);
	}
	return (0);
}