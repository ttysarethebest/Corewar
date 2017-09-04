/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 10:42:05 by tmaske            #+#    #+#             */
/*   Updated: 2017/08/12 10:42:07 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strinc(char *str)
{
	int		i;
	int		len;
	char	*new;

	i = -1;
	if (str)
		len = ft_strlen(str);
	else
		len = 0;
	new = (char*)ft_memalloc(sizeof(char) * (len + 2));
	ft_strcpy(new, str);
	while (++i < (len + 2))
		new[i] = '\0';
	return (new);
}
