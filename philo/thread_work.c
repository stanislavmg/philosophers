/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:33 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/14 14:56:16 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		*handle_one(t_philo *philo);
static int		try_eat(t_philo *philo);
static int		handle_status(t_status status, t_philo *philo);
static void		print_action(int status, const t_philo *philo);

void	*start_routine(void *arg)
{
	t_philo	*philo;
	int		cur_status;

	philo = (t_philo *)arg;
	if (philo->stats->philo_num == 1)
		return (handle_one(philo));
	if (philo->index % 2 == 0)
		ft_usleep(philo->stats->tte);
	cur_status = 0;
	while (cur_status != DEAD && cur_status != FULL && cur_status != STOP)
	{
		if (get_status(philo) == DEAD)
			break ;
		try_eat(philo);
		handle_status(SLEEP, philo);
		handle_status(THINK, philo);
		cur_status = get_status(philo);
	}
	return (NULL);
}

static void	*handle_one(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	handle_status(FORK, philo);
	ft_usleep(philo->stats->ttd);
	handle_status(DEAD, philo);
	pthread_mutex_unlock(philo->left);
	return (NULL);
}

static int	try_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (get_status(philo) == DEAD)
	{
		pthread_mutex_unlock(philo->left);
		return (1);
	}
	handle_status(FORK, philo);
	pthread_mutex_lock(philo->right);
	if (get_status(philo) == DEAD)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return (1);
	}
	handle_status(FORK, philo);
	handle_status(EATING, philo);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

static int	handle_status(t_status status, t_philo *philo)
{
	int		cur_status;

	pthread_mutex_lock(philo->write);
	cur_status = get_status(philo);
	if (STOP == cur_status || DEAD == cur_status || FULL == cur_status)
	{
		pthread_mutex_unlock(philo->write);
		return (1);
	}
	print_action(status, philo);
	pthread_mutex_unlock(philo->write);
	if (DEAD == status)
		set_status(philo, status);
	else if (SLEEP == status)
		ft_usleep(philo->stats->tts);
	else if (EATING == status)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->stats->eat_limit)
			set_status(philo, FULL);
		ft_usleep(philo->stats->tte);
		set_time(philo->lock, &philo->lastmeal, gettime());
	}
	return (0);
}

static void	print_action(int status, const t_philo *philo)
{
	t_ulong	t;

	t = gettime() - get_timestamp(philo);
	if (EATING == status)
		printf("%llu %d is eating\n", t, philo->index);
	else if (SLEEP == status)
		printf("%llu %d is sleep\n", t, philo->index);
	else if (FORK == status)
		printf("%llu %d has taken a fork\n", t, philo->index);
	else if (THINK == status)
		printf("%llu %d is thinking\n", t, philo->index);
}
