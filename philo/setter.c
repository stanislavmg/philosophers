/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:25 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 16:58:55 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time(pthread_mutex_t *lock, t_llong *time, t_llong value)
{
	pthread_mutex_lock(lock);
	*time = value;
	pthread_mutex_unlock(lock);
}

void	set_status(t_philo *philo, int status_)
{
	pthread_mutex_lock(philo->lock);
	philo->status = status_;
	pthread_mutex_unlock(philo->lock);
}
