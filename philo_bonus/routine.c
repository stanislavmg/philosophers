/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:03:02 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/16 13:18:19 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print_action(int status, const t_philo *philo);

int	handle_status(t_status status, t_philo *philo)
{
	if (DEAD == status)
	{
		sem_wait(philo->lock);
		print_action(status, philo);
		return (1);
	}
	sem_wait(philo->lock);
	print_action(status, philo);
	sem_post(philo->lock);
	philo->status = status;
	if (SLEEP == status)
		return (ft_usleep(philo->stats->tts, philo));
	else if (EATING == status)
	{
		if (ft_usleep(philo->stats->tte, philo))
			return (1);
		philo->lastmeal = gettime();
		philo->eat_count++;
		if (philo->eat_count >= philo->stats->eat_limit)
			philo->status = FULL;
	}
	return (0);
}

static void	print_action(int status, const t_philo *philo)
{
	t_ulong	t;

	t = gettime() - philo->timestamp;
	if (DEAD == status)
		printf("%llu %d is died\n", t, philo->index);
	else if (EATING == status)
		printf("%llu %d is eating\n", t, philo->index);
	else if (SLEEP == status)
		printf("%llu %d is sleep\n", t, philo->index);
	else if (FORK == status)
		printf("%llu %d has taken a fork\n", t, philo->index);
	else if (THINK == status)
		printf("%llu %d is thinking\n", t, philo->index);
}

static int	try_eat(t_philo *philo)
{
	int	status;

	status = 0;
	if (sem_wait(philo->forks))
		return (1);
	if (cmp_time(philo))
	{
		sem_post(philo->forks);
		return (handle_status(DEAD, philo));
	}
	handle_status(FORK, philo);
	if (sem_wait(philo->forks))
		return (1);
	if (cmp_time(philo))
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		return (handle_status(DEAD, philo));
	}
	handle_status(FORK, philo);
	if (handle_status(EATING, philo))
		status = 1;
	sem_post(philo->forks);
	sem_post(philo->forks);
	return (status);
}

void	*start_routine(t_philo	*philo)
{
	philo->forks = sem_open(SEM_FORK, 0);
	philo->lock = sem_open(SEM_LOCK, 0);
	if (philo->forks == SEM_FAILED || philo->lock == SEM_FAILED)
		exit (2);
	sem_wait(philo->lock);
	sem_post(philo->lock);
	if (philo->index % 2 == 0)
		ft_usleep(philo->stats->tte, philo);
	while (1)
	{
		if (cmp_time(philo))
			exit(handle_status(DEAD, philo));
		if (try_eat(philo))
			break ;
		if (philo->eat_count >= philo->stats->eat_limit
			&& philo->stats->eat_limit != UNDEFINED)
			exit (0);
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
	philo->forks = sem_open(SEM_FORK, 0);
	if (philo->forks == SEM_FAILED)
		exit (2);
	sem_wait(philo->forks);
	handle_status(FORK, philo);
	ft_usleep(philo->stats->ttd, philo);
	handle_status(DEAD, philo);
	sem_post(philo->forks);
	sem_close(philo->forks);
	exit(0);
}
