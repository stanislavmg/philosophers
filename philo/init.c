/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:09 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 16:58:55 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_stats(t_stats *stats, char **argv);

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
	fill_stats(stats, argv);
	if (check_stats(stats))
	{
		free(stats);
		return (NULL);
	}
	return (stats);
}

static void	fill_stats(t_stats *stats, char **argv)
{
	stats->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(stats->lock, NULL);
	stats->philo_num = ft_atoi(argv[1]);
	stats->thread_count = stats->philo_num;
	stats->ttd = ft_atoi(argv[2]);
	stats->tte = ft_atoi(argv[3]);
	stats->tts = ft_atoi(argv[4]);
	if (argv[5])
		stats->eat_limit = ft_atoi(argv[5]);
	else
		stats->eat_limit = UNDEFINED;
}

int	init_mutex(t_data *data, int num)
{
	int				i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num * 2);
	if (!data->forks)
		return (1);
	data->locks = data->forks + num;
	while (i < num)
	{
		if (pthread_mutex_init(data->forks + i, NULL)
			|| pthread_mutex_init(data->locks + i, NULL))
			return (1);
		i++;
	}
	return (0);
}

t_philo	*init_philo(t_data *data, int num)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*t;

	i = -1;
	philo = (t_philo *)ft_calloc(num, sizeof(t_philo));
	data->write = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->write, NULL);
	if (!philo)
		return (NULL);
	while (++i < num)
	{
		philo[i].write = data->write;
		philo[i].lock = data->locks + i;
		philo[i].index = i + 1;
		philo[i].stats = data->stats;
		philo[i].left = &data->forks[i];
		philo[i].right = &data->forks[(i + 1) % num];
	}
	t = philo[i - 1].right;
	philo[i - 1].right = philo[i - 1].left;
	philo[i - 1].left = t;
	return (philo);
}

int	init_threads(pthread_t *th, t_philo *philo, int n)
{
	int		i;
	t_llong	start_time;

	i = -1;
	start_time = gettime();
	while (++i < n)
	{
		set_time(philo->lock, &philo[i].lastmeal, start_time);
		set_time(philo->lock, &philo[i].timestamp, start_time);
		if (pthread_create(th++, NULL, start_routine, philo + i))
			return (1);
	}
	monitoring((void *)philo);
	return (0);
}
