/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:02:58 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/15 17:55:03 by sgoremyk         ###   ########.fr       */
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

void	start_work(t_philo *philo)
{
	int		i;
	int		status;
	sem_t	*sem_write;
	sem_t	*sem_forks;

	i = 0;
	status = 0;
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_forks = sem_open(SEM_FORK, O_CREAT, 0644, philo->stats->philo_num);
	sem_write = sem_open(SEM_WRITE, O_CREAT, 0644, 1);
	if (sem_forks == SEM_FAILED || sem_write == SEM_FAILED)
		return ;
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
	i = -1;
	while (++i < philo->stats->philo_num)
	{
		wait(&status);
		if (WEXITSTATUS(status) == 1)
		{
			//sem_wait(sem_write);
			i = -1;
			while (++i < philo->stats->philo_num)
				kill(philo[i].pid, SIGTERM);
			//sem_post(sem_write);
		}
	}
}
