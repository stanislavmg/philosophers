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
	else
		return (1);
	while(++i < data->stats->philo_num + 1)
		pthread_join(data->threads[i], &status);
	free_data(data);
	return (0);
}
