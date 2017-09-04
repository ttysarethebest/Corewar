/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 17:41:30 by tmaske            #+#    #+#             */
/*   Updated: 2017/07/19 17:41:44 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	recursiveptr(uintmax_t nbr, char *base, size_t baselen)
{
	if (nbr >= baselen)
	{
		recursiveptr(nbr / baselen, base, baselen);
		recursiveptr(nbr % baselen, base, baselen);
	}
	else
		ft_putchar(base[nbr]);
}

void		ft_putptr(void *p)
{
	uintmax_t	nbr;
	int			base_len;
	char		*base;

	ft_putstr("0x");
	if (p)
	{
		base = "0123456789ABCDEF";
		nbr = (uintmax_t)p;
		base_len = ft_strlen(base);
		recursiveptr(nbr, base, base_len);
	}
	else
		ft_putstr("0");
}
