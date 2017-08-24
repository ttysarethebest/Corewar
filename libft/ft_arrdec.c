/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 18:01:39 by tmaske            #+#    #+#             */
/*   Updated: 2017/08/13 18:01:41 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	loop(int len, char ***n, char ***a, int index)
{
	char	**new;
	char	**arr;
	int		i;
	int		j;

	new = *n;
	arr = *a;
	i = 0;
	j = 0;
	while (i < (len - 1))
	{
		if ((i + j) != index)
		{
			new[i] = arr[i + j];
			i++;
		}
		else
		{
			ft_strdel(&(arr[i]));
			j++;
		}
	}
}

void		ft_arrdec(char ***a, int index, int len)
{
	char	**new;
	char	**arr;

	if (a && *a && **a)
	{
		arr = *a;
		if (len > 1)
		{
			new = (char**)ft_memalloc(sizeof(char*) * (len));
			loop(len, &new, &arr, index);
			new[len - 1] = NULL;
			free(*a);
			*a = new;
		}
	}
}
