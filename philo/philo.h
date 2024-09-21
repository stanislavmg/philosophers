/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:22 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 18:34:09 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define ERR_ARG	-1
# define ERR_MUTEX	-2
# define ERR_MALLOC	-3
# define ERR_THREAD	-4
# define UNDEFINED	-5

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef long long	t_llong;

typedef enum e_status
{
	THINK,
	EATING,
	SLEEP,
	FORK,
	DEAD,
	STOP,
	FULL
}	t_status;

typedef struct s_stats
{
	pthread_mutex_t	*lock;
	int				thread_count;
	int				philo_num;
	int				eat_limit;
	int				ttd;
	int				tte;
	int				tts;
}	t_stats;

typedef struct s_philo
{
	int				index;
	int				eat_count;
	int				status;
	t_llong			lastmeal;
	t_llong			timestamp;
	t_stats			*stats;
	pthread_mutex_t	*write;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	*write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*locks;
	pthread_t		*threads;
	t_stats			*stats;
	t_philo			*all_philo;
}	t_data;

// init
t_data	*init(int argc, char **argv);
t_stats	*init_stats(int argc, char **argv);
t_philo	*init_philo(t_data *data, int num);
int		init_mutex(t_data *data, int num);
int		init_threads(pthread_t *th, t_philo *philo, int n);

// string
t_llong	ft_atoi(char *s);
void	print_error(int err);
int		check_str(char *s);
int		valid_args(int argc, char **argv);

// utils
int		cmp_time(t_philo *philo);
int		check_stats(t_stats *stats);
void	ft_usleep(t_llong sleep_time);
void	*ft_calloc(t_llong nmemb, t_llong size);
void	*free_data(t_data *data);
t_llong	gettime(void);

// thread work
void	*start_routine(void *arg);
void	monitoring(t_philo *philo);

// save setter
void	set_status(t_philo *philo, int status_);
void	set_time(pthread_mutex_t *lock, t_llong *time, t_llong value);

// save getter
int		get_thread_count(int *count, pthread_mutex_t *lock);
int		get_status(t_philo *philo);
t_llong	get_lastmeal(t_philo *philo);
t_llong	get_timestamp(const t_philo *philo);

#endif
