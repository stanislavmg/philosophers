/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_ft_printf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:31 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/03/12 14:42:06 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_printu(size_t num, size_t base, char cap)
{
	char	count;

	count = 1;
	if (!num)
		return (ft_putchar('0'));
	if (num / base != 0)
		count += ft_printu(num / base, base, cap);
	if (num % base < 10)
		ft_putchar(num % base + '0');
	else
		ft_putchar(num % base + cap - 10);
	return (count);
}

char	ft_printx(size_t num, char ch)
{
	if (ch == 'X')
		return (ft_printu(num, 16, 'A'));
	else if (ch == 'x')
		return (ft_printu(num, 16, 'a'));
	else if (!num && (ch == 'x' || ch == 'X'))
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		write(1, "0x", 2);
		return (ft_printu(num, 16, 'a') + 2);
	}
	return (0);
}

size_t	multiplexer(char ch, va_list *args)
{
	size_t	len;

	len = 0;
	if (ch == '%')
		len = ft_putchar('%');
	else if (ch == 'c')
		len = ft_putchar(va_arg(*args, int));
	else if (ch == 's')
		len = ft_putstr(va_arg(*args, char *));
	else if (ch == 'i' || ch == 'd')
		len = ft_putnbr(va_arg(*args, int));
	else if (ch == 'u')
		len = ft_printu(va_arg(*args, unsigned int), 10, 0);
	else if (ch == 'p')
		len = ft_printx(va_arg(*args, unsigned long long), ch);
	else if (ch == 'x' || ch == 'X')
		len = ft_printx(va_arg(*args, unsigned int), ch);
	return (len);
}
