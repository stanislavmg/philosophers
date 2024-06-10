#include "philo.h"

int main(int argc, char **argv)
{
	t_philo *philo;

	// if (argc != 5)
	// 	return (1);
	(void)argc;
	philo = init_philo(argv);
	if (!philo)
		return (1);
	create_threads(philo);
	return (0);
}