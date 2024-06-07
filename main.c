#include "philo.h"

int main(int argc, char **argv)
{
	t_philo *philo;

	philo = init_philo(argv);
	
	return (0);
}

void	start_routine(t_philo *philo)
{
	sleep(1);

}