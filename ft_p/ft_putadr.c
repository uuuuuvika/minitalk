/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:15:36 by vshcherb          #+#    #+#             */
/*   Updated: 2023/06/12 17:37:23 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex_long(unsigned long n, int c)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_puthex_long(n / 16, c);
		len += ft_puthex_long(n % 16, c);
	}
	if (n < 16)
	{
		if (n > 9)
		{
			if (c == 1)
				len += ft_putchar(n + 55);
			else
				len += ft_putchar(n + 87);
		}
		else
			len += ft_putchar(n + 48);
	}
	return (len);
}

int	ft_putadr(unsigned long n)
{
	if (n == 0)
		return (ft_putstr("(nil)"));
	return (ft_putstr("0x") + ft_puthex_long(n, 0));
}
