#ifndef PHILO_H
# define PHILO_H
# define IN_MILISEC(time) (time / 1000)
# define IN_MICROSEC(time) (time * 1000)
/* ERROR CODES */
# define ERR_STATS	-1
# define ERR_MUTEX	-2
# define ERR_MALLOC	-3
# define ERR_THREAD	-4
# define UNDEFINED	-102

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

enum e_status { EATING, SLEEP, THINK, FORK, DEAD };

typedef struct s_stats
{
	int				philo_num;
	int				eat_limit;
	suseconds_t		ttd; // time to die
	suseconds_t		tte; // time to eat
	suseconds_t		tts; // time to sleep
} t_stats;

typedef struct s_philo
{
	pthread_mutex_t	*lock;
	int				index;
	int				*exp;
	int				eat_count;
	int				status;
	size_t			timestamp;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_stats	*stats;
} t_philo;

int		init(char **argv, t_philo **philo, pthread_mutex_t **forks);
int 	create_threads(t_philo *philo, pthread_mutex_t *forks);
void	*start_routine(void *arg);
int		ft_atoi(const char *str);
void	ft_putstr_fd(const char *s, int fd);
void	free_philo(t_philo *philo, pthread_mutex_t *forks, pthread_t *th);
void	*monitoring(void *arg);
int	 	valid_args(int argc, char **argv);

#endif