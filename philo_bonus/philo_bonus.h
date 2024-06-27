#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# define UNDEFINED	-5
# define SEM_NAME "/forks4"

# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <signal.h>

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
    pid_t           pid;
    sem_t           *forks;
	t_stats			*stats;
}	t_philo;

int 	init(char **argv, t_philo **philo);
int 	ft_atoi(const char *str);
long	gettime(void);
int 	valid_args(int argc, char **argv);
void	ft_usleep(long sleep_time);
void	*monitoring(void *arg);
void	*start_routine(void *arg);
void    start_work(t_philo *philo);

#endif