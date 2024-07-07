#include "philo.h"
static int	ft_isspace(char ch)
{
	return ((ch >= '\t' && ch <= '\r') || ch == ' ');
}

void	print_error(int err)
{
	if (ERR_ARG == err)
		printf("Invalid arguments\n");
	else if (ERR_MUTEX == err)
		printf("Mutex error\n");
	else if (ERR_MALLOC == err)
		printf("No memory\n");
	else if (ERR_THREAD == err)
		printf("Thread error\n");
	else
		printf("Unexpected error\n");
}

size_t	ft_atoi(char *s)
{
	int		i;
	size_t	res;

	i = 0;
	res = 0;
	if (!s)
		return (ERR_ARG);
	while (ft_isspace(s[i]))
		i++;
	if (!s[i])
		return (ERR_ARG);
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res *= 10;
		res += s[i] - '0';
		i++;
	}
	while (ft_isspace(s[i]))
		i++;
	if (s[i] || res > INT_MAX)
		return (ERR_ARG);
	return (res);
}
