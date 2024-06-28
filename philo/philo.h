#ifndef PHILO_H
# define PHILO_H

/* ERROR CODES */
# define ERR_STATS	-1
# define ERR_MUTEX	-2
# define ERR_MALLOC	-3
# define ERR_THREAD	-4
# define UNDEFINED	-5

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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
	suseconds_t		ttd; // time to die
	suseconds_t		tte; // time to eat
	suseconds_t		tts; // time to sleep
}	t_stats;

typedef struct s_philo
{
	int				index;
	int				eat_count;
	int				status;
	long			lastmeal;
	size_t			timestamp;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_stats			*stats;
}	t_philo;

t_philo	*init(char **argv, pthread_mutex_t **forks, int *err);
int		create_threads(t_philo *philo, pthread_t *th);
void	*start_routine(void *arg);
int		ft_atoi(const char *str);
void	free_philo(t_philo *philo, pthread_mutex_t *forks, pthread_t *th);
void	*monitoring(void *arg);
int		valid_args(int argc, char **argv);
long	gettime(void);
void	ft_usleep(long sleep_time);
void    *handle_one(void *arg);
int		check_stats(t_stats *stats);
void	print_error(int err);

#endif
