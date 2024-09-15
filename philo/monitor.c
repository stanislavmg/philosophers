/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:18 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/15 16:36:12 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_full(t_philo *philo);

void	monitoring(t_philo *philo)
{
	int			i;
	t_ulong		tmp;
	t_status	cs;

	tmp = get_timestamp(philo);
	while (!check_full(philo))
	{
		i = -1;
		while (++i < philo->stats->philo_num)
		{
			cs = get_status(philo + i);
			if (cmp_time(philo + i) && cs != EATING && cs != FULL)
			{
				pthread_mutex_lock(philo->write);
				set_status(philo + i, DEAD);
				printf("%llu %d is died\n", gettime() - tmp, i + 1);
				i = -1;
				while (++i < philo->stats->philo_num)
					set_status(philo + i, STOP);
				pthread_mutex_unlock(philo->write);
				return ;
			}
		}
	}
}

int	cmp_time(t_philo *philo)
{
	t_ulong	tmp;
	t_ulong	ttd;

	tmp = (gettime() - get_lastmeal(philo));
	ttd = (t_ulong)philo->stats->ttd;
	return (ttd < tmp);
}

static int	check_full(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->stats->philo_num)
	{
		if (get_status(philo + i) != FULL)
			return (0);
	}
	return (1);
}
