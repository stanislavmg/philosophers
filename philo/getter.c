/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:48:18 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 16:58:55 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_llong	get_timestamp(const t_philo *philo)
{
	t_llong	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->timestamp;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}

int	get_thread_count(int *count, pthread_mutex_t *lock)
{
	int	rval;

	pthread_mutex_lock(lock);
	rval = *count;
	pthread_mutex_unlock(lock);
	return (rval);
}

int	get_status(t_philo *philo)
{
	int	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->status;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}

t_llong	get_lastmeal(t_philo *philo)
{
	t_llong	rval;

	pthread_mutex_lock(philo->lock);
	rval = philo->lastmeal;
	pthread_mutex_unlock(philo->lock);
	return (rval);
}
