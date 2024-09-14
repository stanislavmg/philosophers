/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:35:12 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/14 16:01:26 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (++i < data->stats->philo_num)
		pthread_join(data->threads[i], &status);
	free_data(data);
	return (0);
}

t_data	*init(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->stats = init_stats(argc, argv);
	if (!data->stats)
		return (free_data(data));
	if (init_mutex(data, data->stats->philo_num))
		return (data);
	data->all_philo = init_philo(data, data->stats->philo_num);
	if (!data->all_philo)
		return (data);
	data->threads = malloc(sizeof(pthread_t) * (data->stats->philo_num));
	if (!data->threads)
		return (data);
	if (init_threads(data->threads, data->all_philo, data->stats->philo_num))
		return (data);
	return (data);
}
