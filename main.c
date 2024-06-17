#include "philo.h"

int main(int argc, char **argv)
{
	int 			err;
	t_philo 		*philo;
	pthread_mutex_t *forks;

	err = 0;
	philo = NULL;
	forks = NULL;
	if (valid_args(argc, argv))
		return (1);
	err = init(argv, &philo, forks);
	if (err)
		printf("%d\n", err);
	if (!philo)
		return (1);
	create_threads(philo, forks);
	return (0);
}