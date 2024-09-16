/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:03:07 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/16 13:07:48 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_philo(t_philo *philo)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_LOCK);
	free(philo->stats);
	free(philo);
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

t_ulong	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

int	cmp_time(t_philo *philo)
{
	t_ulong	tmp;
	t_ulong	ttd;

	tmp = (gettime() - philo->lastmeal);
	ttd = (t_ulong)philo->stats->ttd;
	return (ttd < tmp);
}

int	ft_usleep(t_ulong sleep_time, t_philo *philo)
{
	t_ulong	start;

	start = gettime();
	while ((gettime() - start) < sleep_time)
	{
		(void)(philo);
		if (cmp_time(philo))
			return (handle_status(DEAD, philo));
		usleep(100);
	}
	return (0);
}
