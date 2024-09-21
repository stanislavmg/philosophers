/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <sgoremyk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:03:05 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/21 18:53:48 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isspace(int ch)
{
	return ((ch >= '\t' && ch <= '\r') || ch == ' ');
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	check_str(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		i++;
		count++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] || count > 10 || 0 == count)
		return (1);
	return (0);
}
