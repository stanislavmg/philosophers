#ifndef PHILO_H
# define PHILO_H
# define IN_MILISEC(time) (time / 1000)
# define IN_MICROSEC(time) (time * 1000)

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
	int				index;
	int				eat_count;
	int				status;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	const t_stats	*stats;
} t_philo;

int 	cmp_time(struct timeval start, struct timeval end, suseconds_t limit);
t_philo	*init_philo(char **argv);
void 	create_threads(t_philo *philo);
void	*start_routine(void *arg);
void	print_action(int status, int index, const t_stats *stats);
int		try_eat(t_philo *philo);
int		ft_atoi(const char *str);

#endif