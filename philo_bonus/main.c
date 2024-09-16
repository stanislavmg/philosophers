/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:02:58 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/16 13:39:23 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	philo = NULL;
	if (valid_args(argc, argv))
		return (1);
	if (init(argv, &philo))
		return (1);
	start_work(philo);
	free_philo(philo);
	return (0);
}

static void	run_philo(t_philo *philo)
{
	int	i;

	i = 0;
	philo->timestamp = gettime();
	while (i < philo->stats->philo_num)
	{
		philo[i].timestamp = philo->timestamp;
		philo[i].lastmeal = philo->timestamp;
		philo[i].pid = fork();
		if (!philo[i].pid && philo->stats->philo_num > 1)
			start_routine(philo + i);
		else if (!philo[i].pid && philo->stats->philo_num == 1)
			handle_one(philo + i);
		i++;
	}
}

void	start_work(t_philo *philo)
{
	int		i;
	int		status;
	sem_t	*sem_forks;
	sem_t	*sem_lock;

	i = 0;
	status = 0;
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_LOCK);
	sem_forks = sem_open(SEM_FORK, O_CREAT, 0644, philo->stats->philo_num);
	sem_lock = sem_open(SEM_LOCK, O_CREAT, 0644, 1);
	(void)sem_lock;
	if (sem_forks == SEM_FAILED)
		return ;
	i = -1;
	sem_wait(sem_lock);
	run_philo(philo);
	sem_post(sem_lock);
	while (++i < philo->stats->philo_num)
	{
		waitpid(-1, &status, 0);
		if (status)
		{
			i = -1;
			while (++i < philo->stats->philo_num)
				kill(philo[i].pid, SIGTERM);
		}
	}
}
