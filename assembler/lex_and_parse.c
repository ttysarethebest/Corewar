/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_and_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaske <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 15:33:38 by tmaske            #+#    #+#             */
/*   Updated: 2017/08/26 15:33:39 by tmaske           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

/*
**	Populates 'v->header' with all required info by calling 'populate_header()'
**	and then creates the cos file and writes the contents of 'v->header' to it
**	by calling the 'init-cor_file()' function. After that it executes the code
**	of lexing/parsing the .s file, and prefroms the function calls to convert
**	what is read into the correct bit-code
**
**	TODO:
**
**	Add code for parsing the rest of the file, starting with:
**	if (v->ret == 0)
**	{
**		//Continue Lex & Parse
**	}
*/

void	lex_and_parse(t_vars *v)
{
	char	blank[8];

	populate_header(v, 0);
	init_cor_file(v, blank);
}

/*
**	Goes through the passed .s file and populates 'v->header' with name and
**	comment if found in the .s file. It counts the total number of lines in the
**	.s file and writes that number to 'v->header->prog_size'.
*/

void	populate_header(t_vars *v, int fd)
{
	char	*line;
	char	*start;
	char	*end;

	line = NULL;
	fd = open(v->c_arg, O_RDONLY);
	while (v->ret == 1)
	{
		v->ret = get_next_line(fd, &line);
		if (v->ret == 1 && (ft_strstr(line, ".name") ||
			ft_strstr(line, ".comment")))
		{
			start = ft_strchr(line, '"') + 1;
			end = ft_strrchr(line, '"');
			if (ft_strstr(line, ".name"))
				ft_strncpy(v->header.prog_name, start, end - start);
			else if (ft_strstr(line, ".comment"))
				ft_strncpy(v->header.comment, start, end - start);
		}
		ft_strdel(&line);
		v->header.prog_size++;
	}
	close(fd);
}

/*
**	Checks 'v->header->prog_name' and 'v->header->comment' for validity. Prints
**	a relevant error if either of them were not found in the .s file. if they
**	are valid then they are written to the .cor file along with the transfromed
**	magic number.
*/

void	init_cor_file(t_vars *v, char *blank)
{
	if (v->header.prog_name[0] && v->header.comment[0])
	{
		v->header.magic = ((v->header.magic >> 24) & 0xff) | ((v->header.magic
			<< 8) & 0xff0000) | ((v->header.magic >> 8) & 0xff00) |
			((v->header.magic << 24) & 0xff000000);
		if (!(v->cor_fd = open(v->cor_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644)))
			ft_putendl("Couldln't create the .cor file.\n");
		else
		{
			write(v->cor_fd, (char *)&v->header.magic, 4);
			ft_bzero(blank, 8);
			write(v->cor_fd, v->header.prog_name, PROG_NAME_LENGTH);
			write(v->cor_fd, blank, 8);
			write(v->cor_fd, v->header.comment, COMMENT_LENGTH);
			write(v->cor_fd, blank, 4);
		}
	}
	else
	{
		if (!(v->header.prog_name[0]))
			ft_putstr("asm Error: No name is defined in ");
		else
			ft_putstr("asm Error: No comment is defined in ");
		ft_putendl(v->c_arg);
	}
}
