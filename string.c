#include "philo.h"
// static char	ft_putchar(int c)
// {
// 	char	ch;

// 	ch = (char)c;
// 	write(1, &ch, 1);
// 	return (1);
// }

static size_t	ft_strlen(const char *s)
{
	const char	*end;

	end = s;
	while (*end)
		end++;
	return (end - s);
}

// static int	ft_putnbr(int n)
// {
// 	unsigned int	num;
// 	int				count;

// 	count = 1;
// 	if (n < 0)
// 		num = n * -1;
// 	else
// 		num = n;
// 	if (n / 10 == 0)
// 	{
// 		if (n < 0)
// 			count += ft_putchar('-');
// 		ft_putchar('0' + num % 10);
// 		return (count);
// 	}
// 	count += ft_putnbr(n / 10);
// 	ft_putchar('0' + num % 10);
// 	return (count);
// }

void	ft_putstr_fd(const char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = ft_strlen(s);
	write(fd, s, i);
}