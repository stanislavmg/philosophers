/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:37 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 18:45:52 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(t_llong nmemb, t_llong size)
{
	char	*pt;
	t_llong	i;
	t_llong	n;

	i = 0;
	n = size * nmemb;
	pt = (char *)malloc(n);
	if (!pt)
		return (NULL);
	while (i < n)
		pt[i++] = 0;
	return ((void *)pt);
}

void	*free_data(t_data *data)
{
	int	i;

	i = -1;
	if (!data)
		return (NULL);
	if (data->stats)
	{
		pthread_mutex_destroy(data->write);
		pthread_mutex_destroy(data->stats->lock);
		while (++i < data->stats->philo_num)
		{
			pthread_mutex_destroy(data->locks + i);
			pthread_mutex_destroy(data->forks + i);
		}
		free(data->stats->lock);
	}
	free(data->forks);
	free(data->threads);
	free(data->stats);
	free(data->all_philo);
	free(data->write);
	free(data);
	return (NULL);
}

void	ft_usleep(t_llong sleep_time)
{
	t_llong	start;

	start = gettime();
	while ((gettime() - start) < sleep_time)
		usleep(250);
}

t_llong	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
