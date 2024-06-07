#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "ft_printf/ft_printf.h"
/*** status ***/
# define EATING		1
# define SLEEPING	2
# define THINKING	3
# define FORK		4
# define DIE		5

typedef struct s_stats
{
	size_t	philo_num;
	size_t	ttd; // time to die
	size_t	tte; // time to eat
	size_t	tts; // time to sleep
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
int	ft_atoi(const char *str);

#endif