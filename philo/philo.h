#ifndef PHILO_H
# define PHILO_H

/* ERROR CODES */
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
	int	philo_num;
	int	eat_limit;
	int	ttd; // time to die
	int	tte; // time to eat
	int	tts; // time to sleep
}	t_stats;

typedef struct s_philo
{
	int				index;
	int				eat_count;
	int				status;
	long			lastmeal;
	size_t			timestamp;
	t_stats			*stats;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_philo;

typedef struct s_data
{
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
int 	init_mutex(t_data *data, int num);
int		init_threads(pthread_t *th, t_philo *philo, int n);
// string
size_t	ft_atoi(char *s);
void	print_error(int err);
// utils
int		check_stats(t_stats *stats);
void	ft_usleep(long sleep_time);
long	gettime(void);
int		get_status(t_philo *philo);
void	set_status(t_philo *philo, int status_);
void	*ft_calloc(size_t nmemb, size_t size);
void	*free_data(t_data *data);
// thread work
void	*start_routine(void *arg);
void	*monitoring(void *arg);

#endif
