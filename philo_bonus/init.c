/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:02:55 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 17:53:19 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!st || !st->philo_num)
		return (NULL);
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
		philo[i].lock = 0;
	}
	return (philo);
}
int	check_stats(t_stats *stats);

int	init(char **argv, t_philo **philo)
{
	t_stats	*st;

	st = init_stats(argv);
	if (check_stats(st))
	{
		free(st);
		return (1);
	}
	*philo = init_philo(st);
	if (!philo)
	{
		free(st);
		return (1);
	}
	return (0);
}

int	check_stats(t_stats *stats)
{
	if (stats->eat_limit == 0 || stats->philo_num == 0)
		return (1);
	if (stats->ttd < 0
		|| stats->tte < 0
		|| stats->tts < 0
		|| stats->philo_num < 0
		|| (stats->eat_limit < 0 && stats->eat_limit != UNDEFINED))
	{
		printf("Incorrect arguments\n");
		return (1);
	}
	return (0);
}
