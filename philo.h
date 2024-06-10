#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
/*** status ***/
enum e_status { e_eating, e_sleep, e_think, e_fork, e_dead };

typedef struct s_stats
{
	int		philo_num;
	suseconds_t		ttd; // time to die
	suseconds_t		tte; // time to eat
	suseconds_t		tts; // time to sleep
} t_stats;

typedef struct s_philo
{
	int				index;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				eat_count;
	int				status;
	t_stats			stats;
} t_philo;

t_philo	*init_philo(char **argv);
void create_threads(t_philo *philo);
void	*start_routine(void *arg);
void	print_action(t_philo *philo, size_t time);
int	try_eat(t_philo *philo);
int	ft_atoi(const char *str);

#endif