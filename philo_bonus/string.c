#include "philo_bonus.h"

// static size_t	ft_strlen(const char *s)
// {
// 	const char	*end;

// 	end = s;
// 	while (*end)
// 		end++;
// 	return (end - s);
// }

// static void	ft_putstr_fd(const char *s, int fd)
// {
// 	size_t	i;

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
