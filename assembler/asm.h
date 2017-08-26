/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:32:12 by tmaske            #+#    #+#             */
/*   Updated: 2017/08/24 15:32:13 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>

# define MAX_OPTS 1

typedef struct		s_vars
{
	int				i;
	int				ret;
	int				num_opts;
	int				num_args;
	char			*test_path;
	char			*test_file;
	char			**paths;
	char			**files;
	char			**args;
	char			options[MAX_OPTS + 1];
}					t_vars;

int					main(int argc, char **argv);
void				init(t_vars *v);
void				ft_exit(t_vars *v, int argc);
void				ft_asm(t_vars *v);

void				add_option(char *str, t_vars *v, int i);
void				add_arg(char *arg, t_vars *v);
int					test_arg(t_vars *v, char *arg, int arg_len);
int					test_file_dir(t_vars *v, char *arg);
void				print_verbose(t_vars *v, char *path, int test);

#endif
