/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 14:05:56 by tmaske            #+#    #+#             */
/*   Updated: 2017/08/22 14:05:58 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
**	Goes through options string 'str' looking for valid options. Adds one to
**	the 'options' array in 'v' if found and increments'num_opts'.
*/

void	add_option(char *str, t_vars *v, int i)
{
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] == 'v' || str[i] == 'v')
		{
			if (ft_strchr(v->options, str[i]) == NULL)
			{
				v->options[v->num_opts] = str[i];
				v->num_opts++;
			}
		}
		else
		{
			ft_putstr("Ignored invalid option: ");
			ft_putendl(&str[i]);
		}
	}
}

/*
**	Takes in a string argument 'arg' and tests it using 'test_args()'. If the
**	arg is valid, it is added to 'v->args', otherwise a relevant error is
**	displayed. Prints out the processing details if 'v' was selected as an
**	option.
*/

void	add_arg(char *arg, t_vars *v)
{
	int		test;

	if ((test = test_arg(v, arg, ft_strlen(arg))) == 0)
	{
		ft_arrinc(&(v->args), arg, v->num_args);
		v->num_args++;
	}
	if (ft_strcmp(v->test_path, arg) != 0 && ft_strcmp(v->test_path, ".") != 0)
		free(v->test_path);
	if (ft_strchr(v->options, 'v'))
		print_verbose(v, arg, test);
	if (test != 0)
	{
		ft_putstr("asm Error: ");
		if (test == -1)
			ft_putstr("Does not exist: ");
		else if (test == -2)
			ft_putstr("Path is not valid: ");
		else if (test == -3)
			ft_putstr("File is not a valid type: ");
		ft_putendl(arg);
	}
}

/*
**	Takes in a string argument 'arg' and its len, check's the type of the
**	argument, if it is ".s", it checks to see if the file exits using
**	'test_file_dir()' and returns an int depending on the result.
**
**	Return Values:
**	-3 : The argument did not specify a valid file
**	-2 : The argument did not specify a valid path
**	-1 : The argument does not exist
**	 0 : The argument is valid and exists
*/

int		test_arg(t_vars *v, char *arg, int arg_len)
{
	DIR		*d;
	char	*temp;
	int		path_len;

	v->test_path = arg;
	v->test_file = arg;
	if (arg[arg_len - 2] != '.' && arg[arg_len - 1] != 's')
		return (-3);
	else if (((temp = ft_strrchr(arg, '/')) != NULL))
	{
		path_len = arg_len - ft_strlen(temp + 1);
		v->test_path = ft_strsub(arg, 0, path_len - 1);
		v->test_file = (arg + path_len);
	}
	else
		v->test_path = ".";
	d = opendir(v->test_path);
	if (d == NULL)
		return (-2);
	else
	{
		closedir(d);
		return (test_file_dir(v));
	}
}

/*
**	Sreachers for 'v->test_file' inside the dir 'v->test_path' and returns an
**	int depening on the result.
**
**	Return Values:
**	-1 : The argument path or does not exist
**	 0 : The argument is valid and exists
*/

int		test_file_dir(t_vars *v)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(v->test_path);
	while ((dir = readdir(d)) != NULL)
	{
		if (ft_strcmp(dir->d_name, v->test_file) == 0)
			return (0);
	}
	return (-1);
}

/*
**	Prints out the results of arugument valadation testing
*/

void	print_verbose(t_vars *v, char *path, int test)
{
	ft_putstr("\nProcessing Path: ");
	ft_putendl(path);
	ft_putstr("Test Arg Status: ");
	ft_putnendl(test);
	ft_putstr("Processed Path: ");
	ft_putendl(v->test_path);
	ft_putstr("Processed File: ");
	ft_putendl(v->test_file);
	ft_putendl("\nPost Processing\nArgs Array: ");
	ft_arrprint(v->args);
	ft_putstr("\n");
}
