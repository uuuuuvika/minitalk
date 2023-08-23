/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:11:55 by vshcherb          #+#    #+#             */
/*   Updated: 2023/06/13 15:45:01 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_format(const char i, va_list list, int count)
{
	if (i == '%')
		count += ft_putchar('%');
	if (i == 'c')
		count += ft_putchar((char)va_arg(list, int));
	else if (i == 's')
		count += ft_putstr(va_arg(list, char *));
	else if (i == 'p')
		count += ft_putadr(va_arg(list, unsigned long));
	else if (i == 'd' || i == 'i')
		count += ft_putnbr(va_arg(list, int));
	else if (i == 'u')
		count += ft_putunsigned(va_arg(list, unsigned int));
	else if (i == 'x')
		count += ft_puthex(va_arg(list, unsigned int), 0);
	else if (i == 'X')
		count += ft_puthex(va_arg(list, unsigned int), 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count = check_format(format[++i], list, count);
			i++;
		}
		else
		{
			count += ft_putchar(format[i]);
			i++;
		}
	}
	va_end(list);
	return (count);
}

// int main()
// {
//     unsigned int num = 4294967295;
//     char *vika = NULL;
// 	int to_hex = 283645;
//     int original_result = printf("%u %p %p %X\n", num, vika, &vika, to_hex);
//     int my_result = ft_printf("%u %p %p %X\n", num, vika, &vika, to_hex);
//     printf("%i\n", original_result);
//     printf("%i\n", my_result);
// }