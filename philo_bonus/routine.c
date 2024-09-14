/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:03:02 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/14 16:45:46 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static int	handle_status(t_status status, t_philo *philo)
// {
// 	int		cur_status;

// 	pthread_mutex_lock(philo->write);
// 	cur_status = get_status(philo);
// 	if (STOP == cur_status || DEAD == cur_status || FULL == cur_status)
// 	{
// 		pthread_mutex_unlock(philo->write);
// 		return (1);
// 	}
// 	print_action(status, philo);
// 	pthread_mutex_unlock(philo->write);
// 	if (DEAD == status)
// 		set_status(philo, status);
// 	else if (SLEEP == status)
// 		ft_usleep(philo->stats->tts);
// 	else if (EATING == status)
// 	{
// 		philo->eat_count++;
// 		if (philo->eat_count == philo->stats->eat_limit)
// 			set_status(philo, FULL);
// 		ft_usleep(philo->stats->tte);
// 		set_time(philo->lock, &philo->lastmeal, gettime());
// 	}
// 	return (0);
// }

// static void	print_action(int status, const t_philo *philo)
// {
// 	t_ulong	t;

// 	t = gettime() - get_timestamp(philo);
// 	if (EATING == status)
// 		printf("%llu %d is eating\n", t, philo->index);
// 	else if (SLEEP == status)
// 		printf("%llu %d is sleep\n", t, philo->index);
// 	else if (FORK == status)
// 		printf("%llu %d has taken a fork\n", t, philo->index);
// 	else if (THINK == status)
// 		printf("%llu %d is thinking\n", t, philo->index);
// }

static int	handle_status(int status, t_philo *philo)
{
	t_ulong	t;

	t = gettime();
	if (STOP == philo->status)
		return (1);
	else if (DEAD == status)
	{
		printf("%lld %d died\n", t - philo->timestamp, philo->index);
		philo->status = status;
		return (1);
	}
	else if (EATING == status)
	{
		printf("%lld %d is eating\n", t - philo->timestamp, philo->index);
		philo->eat_count++;
		philo->lastmeal = t;
		ft_usleep(philo->stats->tte);
	}
	else if (SLEEP == status)
	{
		printf("%lld %d is sleep\n", t - philo->timestamp, philo->index);
		ft_usleep(philo->stats->tts);
	}
	else if (FORK == status)
		printf("%lld %d has taken a fork\n", t - philo->timestamp, philo->index);
	else if (THINK == status)
		printf("%lld %d is thinking\n", t - philo->timestamp, philo->index);
	else
		printf("Error: unexpected status\n");
	return (0);
}

static int	cmp_time(t_philo *philo)
{
	return (philo->stats->ttd < (gettime() - philo->lastmeal));
}

static int	try_eat(t_philo *philo)
{
	sem_wait(philo->forks);
	if (cmp_time(philo))
	{
		sem_post(philo->forks);
		handle_status(DEAD, philo);
		return (1);
	}
	handle_status(FORK, philo);
	sem_wait(philo->forks);
	if (cmp_time(philo))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		handle_status(DEAD, philo);
		return (1);
	}
	handle_status(FORK, philo);
	handle_status(EATING, philo);
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (0);
}

void	*start_routine(t_philo	*philo)
{
	philo->forks = sem_open(SEM_NAME, 0);
	if (philo->forks == SEM_FAILED)
		exit (2);
	if (philo->index % 2 == 0)
		ft_usleep(philo->stats->tte);
	while (1)
	{
		if (cmp_time(philo))
			philo->status = DEAD;
		if (philo->status == DEAD)
		{
			handle_status(DEAD, philo);
			break ;
		}
		if (STOP == philo->status || try_eat(philo))
			break ;
		if (philo->eat_count >= philo->stats->eat_limit
			&& philo->stats->eat_limit != UNDEFINED)
		{
			philo->status = FULL;
			sem_close(philo->forks);
			exit(0);
		}
		if (handle_status(SLEEP, philo))
			break ;
		if (handle_status(THINK, philo))
			break ;
	}
	sem_close(philo->forks);
	exit(1);
}

void	handle_one(t_philo *philo)
{
	philo->forks = sem_open(SEM_NAME, 0);
	if (philo->forks == SEM_FAILED)
		exit (2);
	sem_wait(philo->forks);
	handle_status(FORK, philo);
	ft_usleep(philo->stats->ttd);
	handle_status(DEAD, philo);
	sem_post(philo->forks);
	sem_close(philo->forks);
	exit(0);
}
