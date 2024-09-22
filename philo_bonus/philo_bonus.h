/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:02:50 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/22 15:50:09 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define UNDEFINED	-5
# define SEM_FORK "/fork"
# define SEM_LOCK "/lock"

# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

typedef long long	t_llong;

typedef enum e_status
{
	EATING,
	SLEEP,
	THINK,
	FORK,
	DEAD,
	STOP,
	FULL
}	t_status;

typedef struct s_stats
{
	int				philo_num;
	int				eat_limit;
	suseconds_t		ttd;
	suseconds_t		tte;
	suseconds_t		tts;
}	t_stats;

typedef struct s_philo
{
	int				index;
	int				eat_count;
	int				status;
	t_llong			lastmeal;
	t_llong			timestamp;
	pid_t			pid;
	sem_t			*forks;
	sem_t			*lock;
	t_stats			*stats;
}	t_philo;

int		init(char **argv, t_philo **philo);
int		ft_atoi(const char *str);
t_llong	gettime(void);
void	free_philo(t_philo *philo);
int		valid_args(int argc, char **argv);
int		ft_usleep(t_llong sleep_time, t_philo *philo);
void	*start_routine(t_philo	*philo);
void	start_work(t_philo *philo);
void	handle_one(t_philo *philo);
int		cmp_time(t_philo *philo);
int		handle_status(t_status status, t_philo *philo);
int		check_str(char *s);

#endif