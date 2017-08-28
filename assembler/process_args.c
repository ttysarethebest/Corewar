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
**	arg is valid, it's path is added to 'v->paths' and its filename to
**	'v->files', otherwise a relevant error is displayed. Prints out the
**	processing details if 'v' was selected as an option.
*/

void	add_arg(char *arg, t_vars *v)
{
	int		test;

	if ((test = test_arg(v, arg, ft_strlen(arg))) == 0)
	{
		ft_arrinc(&(v->paths), v->c_path, v->num_args);
		ft_arrinc(&(v->files), v->c_file, v->num_args);
		ft_arrinc(&(v->args), arg, v->num_args);
		v->num_args++;
	}
	if (ft_strcmp(v->c_path, arg) != 0 && ft_strcmp(v->c_path, ".") != 0)
		free(v->c_path);
	if (ft_strchr(v->options, 'v'))
		print_verbose(v, arg, test);
	if (test != 0)
	{
		if (test == -1)
			ft_putstr("asm Error: Insufficient permissions to access file: ");
		else if (test == -2)
			ft_putstr("asm Error: The specified file does not exist: ");
		else if (test == -3)
			ft_putstr("asm Error: The specified path does not exist: ");
		else if (test == -4)
			ft_putstr("asm Error: The specified file has an invalid type: ");
		ft_putendl(arg);
	}
}

/*
**	Takes in a string argument 'arg' and its len, check's the type of the
**	argument, if it is ".s", it checks to see if the file exits using
**	'c_file_dir()' and returns an int depending on the result.
**
**	Return Values:
**	 0 : The argument is valid and exists
**	-1 : Insufficient permissions to access file
**	-2 : The specified file does not exist
**	-3 : The specified path does not exist
**	-4 : The specified file has an invalid type
*/

int		test_arg(t_vars *v, char *arg, int arg_len)
{
	DIR		*d;
	char	*temp;
	int		path_len;

	v->c_file = arg;
	if (ft_strcmp(&arg[arg_len - 2], ".s") != 0)
		return (-4);
	if (((temp = ft_strrchr(arg, '/')) != NULL))
	{
		path_len = arg_len - ft_strlen(temp + 1);
		v->c_path = ft_strsub(arg, 0, path_len - 1);
		v->c_file = (arg + path_len);
	}
	else
		v->c_path = ".";
	d = opendir(v->c_path);
	if (d == NULL)
		return (-3);
	else
	{
		closedir(d);
		return (test_file_dir(v, arg));
	}
}

/*
**	Searches for 'v->c_file' inside the dir 'v->c_path'. If found it
**	attempts to open the file and returns an int depening on the result.
**
**	Return Values:
**	 0 : The argument is valid and exists
**	-1 : Insufficient permissions to access file
**	-2 : The file does not exist
*/

int		test_file_dir(t_vars *v, char *arg)
{
	DIR				*d;
	struct dirent	*dir;
	struct stat		stats;
	int				flag;

	flag = 0;
	d = opendir(v->c_path);
	while ((dir = readdir(d)) != NULL)
	{
		if (ft_strcmp(dir->d_name, v->c_file) == 0)
			flag = 1;
	}
	closedir(d);
	if (flag == 1)
	{
		if (lstat(arg, &stats) != -1)
		{
			if (stats.st_mode & S_IROTH)
				return (0);
		}
		return (-1);
	}
	return (-2);
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
	ft_putendl(v->c_path);
	ft_putstr("Processed File: ");
	ft_putendl(v->c_file);
	ft_putendl("\nPost Processing\nArgs Array: ");
	ft_arrprint(v->args);
	ft_putstr("\n");
}
