

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/22 21:43:02 by carmand           #+#    #+#              #
#    Updated: 2017/10/18 23:25:04 by carmand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCDIR = src
SRC = free_sh.c built_env.c exec.c get_line.c main.c search_bin.c \
	cd_minishell.c build_echo.c help_cd.c intro.c help2_cd.c \
	help3_cd.c help4_cd.c help5_cd.c help_env.c help2_env.c \
	help6_cd.c minishell.c init_sh.c serach_builtin.c

OBJDIR = obj
OBJ = $(SRC:.c=.o)

LIBDIR = libft
LIB = ft

CFLAGS = -Wall -Wextra -Werror -g

all: $(LIBDIR)/lib$(LIB).a $(OBJDIR) $(NAME)

$(LIBDIR)/lib$(LIB).a:
	@make -C $(LIBDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ))
	@$(CC) $(CFLAGS) $(addprefix $(OBJDIR)/, $(OBJ)) -o $(NAME) -L $(LIBDIR) -l $(LIB)
	@tput setaf 77 ; echo [DONE]

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo compiled $<

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBDIR)

re: fclean all

.PHONY: re fclean clean all
