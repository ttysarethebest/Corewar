/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:32:06 by tmaske            #+#    #+#             */
/*   Updated: 2017/08/24 15:32:08 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
**	Processes arguments using 'add_option()' & 'add_path()'. Prints out the
**	selected options if 'v' was selected as an option.
*/

int		main(int argc, char **argv)
{
	t_vars	v;
	int		i;

	i = -1;
	init(&v);
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			add_option(argv[i], &v, 0);
		else
			add_arg(argv[i], &v);
	}
	if (ft_strchr(v.options, 'v'))
	{
		ft_putstr("\nSelected Options: ");
		ft_putendl(v.options);
	}
	if (v.num_args == 0)
		v.ret = -1;
	while (v.ret == 0 && ++v.i < v.num_args)
		ft_asm(&v);
	ft_exit(&v);
	return (v.ret);
}

/*
**	Initializes all variables inside the 'v' structure.
*/

void	init(t_vars *v)
{
	int i;

	i = -1;
	v->i = -1;
	v->ret = 0;
	v->num_opts = 0;
	v->num_args = 0;
	v->test_path = NULL;
	v->test_file = NULL;
	v->args = NULL;
	while (++i < MAX_OPTS + 2)
		v->options[i] = '\0';
}

/*
**	Frees all variables inside the 'v' structure.
*/

void	ft_exit(t_vars *v)
{
	int i;

	i = -1;
	if (v->ret == -1)
		ft_putendl("asm Error: No valid file specified. Exiting.");
	while (++i < v->num_args)
		free(v->args[i]);
	free(v->args);
}

/*
**	Poops in your moms face.
*/

void	ft_asm(t_vars *v)
{
	ft_putstr("Compiling ");
	ft_putstr(v->args[v->i]);
	ft_putstr(" at index ");
	ft_putnbr(v->i);
	ft_putendl(".");
	v->ret = 1;
}
