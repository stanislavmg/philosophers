/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:17 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/03/12 14:41:44 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	int		i;
	size_t	count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, s);
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '%')
		{
			count += i;
			write(1, s, i++);
			count += multiplexer(s[i], &args);
			s += i + 1;
			i = -1;
		}
		i++;
	}
	count += ft_putstr((char *)s);
	va_end(args);
	return (count);
}
