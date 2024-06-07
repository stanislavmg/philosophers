/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgoremyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:26 by sgoremyk          #+#    #+#             */
/*   Updated: 2024/03/12 14:42:28 by sgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

char	ft_printu(size_t num, size_t base, char cap);
char	ft_printx(size_t num, char ch);
size_t	multiplexer(char ch, va_list *args);
int		ft_printf(const char *s, ...);
char	ft_putchar(int c);
size_t	ft_putstr(char *s);
char	ft_putnbr(int n);

#endif
