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
		return (1);
	err = init(argv, &philo, &forks);
	if (err)
		printf("%d\n", err);
	if (!philo)
		return (1);
	th = (pthread_t *)malloc(sizeof(pthread_t) * philo->stats->philo_num + 1);
	if (!th)
		return (1);
	create_threads(philo, th);
	free_philo(philo, forks, th);
	return (0);
}
