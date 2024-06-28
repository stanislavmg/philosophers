#include "philo.h"

int	main(int argc, char **argv)
{
	int				err;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		*th;

	err = 0;
	philo = NULL;
	forks = NULL;
	th = NULL;
	if (valid_args(argc, argv))
		print_error(ERR_STATS);
	philo = init(argv, &forks, &err);
	if (err || !philo)
		print_error(err);
	th = (pthread_t *)malloc(sizeof(pthread_t) * philo->stats->philo_num + 1);
	if (!th)
		print_error(ERR_MALLOC);
	err = create_threads(philo, th);
	if (err)
		print_error(err);
	free_philo(philo, forks, th);
	return (0);
}

void	print_error(int err)
{
	if (ERR_STATS == err)
		printf("Invalid arguments\n");
	else if (ERR_MUTEX == err)
		printf("Mutex error\n");
	else if (ERR_MALLOC == err)
		printf("No memory\n");
	else if (ERR_THREAD == err)
		printf("Thread error\n");
	exit(EXIT_FAILURE);
}