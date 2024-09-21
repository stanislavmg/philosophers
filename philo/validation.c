/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:45:12 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 18:47:02 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stats(t_stats *stats)
{
	if (stats->eat_limit == 0 || stats->philo_num == 0)
		return (1);
	if (stats->ttd < 0
		|| stats->tte < 0
		|| stats->tts < 0
		|| stats->philo_num < 0
		|| (stats->eat_limit < 0 && stats->eat_limit != UNDEFINED))
	{
		printf("Incorrect arguments\n");
		return (1);
	}
	return (0);
}

int	valid_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments!\n"
			"philo take the following args:\n"
			"number_of_philosophers time_to_die time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	while (argv[++i])
	{
		if (check_str(argv[i]))
		{
			printf("Incorrect argument: %s\n"
				"Please enter an positive integer number\n", argv[i]);
			return (1);
		}
	}
	return (0);
}
