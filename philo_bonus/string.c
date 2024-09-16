/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:03:05 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/09/16 13:10:51 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static t_ulong	ft_strlen(const char *s)
// {
// 	const char	*end;

// 	end = s;
// 	while (*end)
// 		end++;
// 	return (end - s);
// }

// static void	ft_putstr_fd(const char *s, int fd)
// {
// 	t_ulong	i;

// 	if (!s)
// 		return ;
// 	i = ft_strlen(s);
// 	write(fd, s, i);
// }

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;
	int	i;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
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
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while ('0' == s[i])
		i++;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		i++;
		count++;
	}
	while (s[i] && ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' '))
		i++;
	if (s[i] || count > 10 || 0 == count)
		return (1);
	return (0);
}
