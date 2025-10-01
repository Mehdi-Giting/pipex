/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:38:04 by marvin            #+#    #+#             */
/*   Updated: 2025/04/06 16:38:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s)
	{
		while (s[i])
		{
			count += ft_putchar(s[i]);
			i++;
		}
	}
	else if (s == NULL)
		count += ft_putstr("(null)");
	return (count);
}

int	ft_putnbr(int n)
{
	long	ln;
	int		count;

	ln = (long)n;
	count = 0;
	if (ln < 0)
	{
		ft_putchar('-');
		ln = ln * -1;
		count++;
	}
	if (ln > 9)
	{
		count += ft_putnbr(ln / 10);
		count += ft_putnbr(ln % 10);
	}
	else
		count += ft_putchar((ln % 10) + '0');
	return (count);
}

int	ft_putunsigned(unsigned int n)
{
	long	ln;
	int		count;

	ln = (long)n;
	count = 0;
	if (ln > 9)
		count += ft_putnbr(ln / 10);
	count += ft_putchar((ln % 10) + '0');
	return (count);
}
