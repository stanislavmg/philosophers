#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;
	void	*status;

	i = 0;
	status = NULL;
	data = init(argc, argv);
	if (data)
		pthread_join(data->threads[i], status);
	while(++i < data->stats->philo_num + 1)
		pthread_join(data->threads[i], &status);
	free_data(data);
	return (0);
}
