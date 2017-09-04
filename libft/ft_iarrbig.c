/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iarrbig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 17:38:51 by tmaske            #+#    #+#             */
/*   Updated: 2017/07/19 17:38:51 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_iarrbig(int *arr, int len)
{
	int i;
	int temp;

	i = 0;
	temp = -2147483647;
	while (i < len)
	{
		if (arr[i] > temp)
			temp = arr[i];
		i++;
	}
	return (temp);
}
