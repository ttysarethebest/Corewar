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

	i = 0;
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
	ft_exit(&v, argc);
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
	v->c_path = NULL;
	v->c_file = NULL;
	v->c_arg = NULL;
	v->cor_path = NULL;
	v->cor_file = NULL;
	v->cor_arg = NULL;
	v->cor_fd = -1;
	v->paths = NULL;
	v->files = NULL;
	v->args = NULL;
	v->header.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(v->header.prog_name, PROG_NAME_LENGTH + 1);
	v->header.prog_size = 0;
	ft_bzero(v->header.comment, COMMENT_LENGTH + 1);
	while (++i < MAX_OPTS + 2)
		v->options[i] = '\0';
}

/*
**	Frees all variables inside the 'v' structure & prints out errors and
**	warnings if necessary.
*/

void	ft_exit(t_vars *v, int argc)
{
	int i;

	i = -1;
	if (v->ret == -1 && argc == 1)
		ft_putendl("Usage :\n./asm file_name[.s] ...");
	while (++i < v->num_args)
	{
		free(v->paths[i]);
		free(v->files[i]);
		free(v->args[i]);
	}
	free(v->paths);
	free(v->files);
	free(v->args);
}

/*
**	Poops in your moms face.
*/

void	ft_asm(t_vars *v)
{
	v->ret = 1;
	v->c_path = v->paths[v->i];
	v->c_file = v->files[v->i];
	v->c_arg = v->args[v->i];
	create_s_vars(v, 0);
	ft_putstr("Compiling ");
	ft_putstr(v->args[v->i]);
	ft_putstr(" at index ");
	ft_putnbr(v->i);
	ft_putendl(".");
	lex_and_parse(v);
	ft_strdel(&v->cor_arg);
	ft_strdel(&v->cor_path);
}

/*
**	Populates v->cor_arg, 'v->cor_path' & 'v->cor_file' with approapreate names
**	and prints them out if 'v' was selected as an option.
*/

void	create_s_vars(t_vars *v, int len)
{
	char	*temp;
	
	len = ft_strstr(v->c_arg, ".s") - v->c_arg;
	v->cor_arg = (char*)ft_memalloc(sizeof(char) * (len + 5));
	ft_strncpy(v->cor_arg, v->c_arg, len);
	ft_strcat(v->cor_arg, ".cor");
	v->cor_file = v->cor_arg;
	if (((temp = ft_strrchr(v->cor_arg, '/')) != NULL))
	{
		len = ft_strlen(v->cor_arg) - ft_strlen(temp + 1);
		v->cor_path = ft_strsub(v->cor_arg, 0, len - 1);
		v->cor_file = (v->cor_arg + len);
	}
	else
		v->cor_path = ".";
	if (ft_strchr(v->options, 'v'))
	{
		ft_putstr("\nProcessing Cor Variables:\nCor Arg: ");
		ft_putendl(v->cor_arg);
		ft_putstr("Cor Path: ");
		ft_putendl(v->cor_path);
		ft_putstr("Cor File: ");
		ft_putendl(v->cor_file);
	}
}
