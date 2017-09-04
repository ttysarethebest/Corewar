# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaske <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/24 15:32:28 by tmaske            #+#    #+#              #
#    Updated: 2017/08/24 15:32:31 by tmaske           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HLOC = includes
LIBFT = libft/libft.a

ASMNAME = asm
ASMLOC = assembler/
ASMFILES =	$(HLOC)op.c\
			$(ASMLOC)asm.c\
			$(ASMLOC)process_args.c\
			$(ASMLOC)lex_and_parse.c
ASMOBJECTS =	asm.o\
				process_args.o\
				lex_and_parse.o
ASMFLAGS = -Wall -Werror -Wextra -I$(HLOC) -c -g -g3

$(ASMNAME): fclean
	@gcc $(ASMFLAGS) $(ASMFILES)
	@gcc -o $(ASMNAME) $(ASMOBJECTS) $(LIBFT)
	@echo "asm Compiled"

all: $(ASMNAME)

libft:
	@make -C libft/ re
	@echo "Libft Cleaned & Compiled"

clean:
	@rm -f $(ASMOBJECTS)
	@echo "asm Cleaned"

fclean: clean
	@rm -f $(ASMSNAME)
	@echo "asm Executable Deleted"

mclean:
	@find . -name '._*' -type f -delete
	@find . -name '.DS_Store' -type f -delete
	@echo "Removed hidden ._ files."

re: clean fclean libft all

norm:
	#@make -C libft/ norm
	#@echo "\nNorme asm"
	@norminette -R CheckForbiddenSourceHeader $(ASMFILES) $(ASMHEADER)
	@echo "\nNorme Check Completed"