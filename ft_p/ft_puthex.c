/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:16:47 by vshcherb          #+#    #+#             */
/*   Updated: 2023/06/12 17:24:04 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, int c)
{
	int	len;

	len = 0;
	if (n >= 16)
	{
		len += ft_puthex(n / 16, c);
		len += ft_puthex(n % 16, c);
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
