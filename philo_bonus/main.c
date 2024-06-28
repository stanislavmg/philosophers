#include "philo_bonus.h"

int main(int argc, char **argv)
{
	t_philo			*philo;

	philo = NULL;
	if (valid_args(argc, argv))
		return (1);
	init(argv, &philo);
	if (!philo)
		return (1);
    start_work(philo);
    free_philo(philo);
    return (0);
}

void    start_work(t_philo *philo)
{
    int i;
    int status;
    sem_t	*sem;

    i = 0;
    status = 0;
    sem_unlink(SEM_NAME);
	sem = sem_open(SEM_NAME, O_CREAT, 0644, philo->stats->philo_num);
    if (sem == SEM_FAILED)
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
    while(++i < philo->stats->philo_num)
    {
        wait(&status);
        if (status)
        {
            i = -1;
            while(++i < philo->stats->philo_num)
                kill(philo[i].pid, SIGTERM);
        }
    }
}