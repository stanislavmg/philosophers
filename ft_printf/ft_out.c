/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:10 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/03/12 14:41:01 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_putchar(int c)
{
	char	ch;

	ch = (char)c;
	write(1, &ch, 1);
	return (1);
}

size_t	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i++;
	write(1, s, i);
	return (i);
}

char	ft_putnbr(int n)
{
	unsigned int	num;
	char			count;

	count = 1;
	if (n < 0)
		num = n * -1;
	else
		num = n;
	if (n / 10 == 0)
	{
		if (n < 0)
			count += ft_putchar('-');
		ft_putchar('0' + num % 10);
		return (count);
	}
	count += ft_putnbr(n / 10);
	ft_putchar('0' + num % 10);
	return (count);
}
