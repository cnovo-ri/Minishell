# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 07:18:27 by cnovo-ri          #+#    #+#              #
#    Updated: 2017/10/30 07:35:28 by cnovo-ri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCDIR = src
SRC = built_env.c get_line.c main.c search_bin.c cd_minishell.c help_cd.c \
	intro.c help2_cd.c help3_cd.c help4_cd.c help5_cd.c help_env.c init_sh.c \
	help2_env.c search_builtin.c get_path.c

OBJDIR = obj
OBJ = $(SRC:.c=.o)

LIBDIR = libft
LIB = ft

CFLAGS = -Wall -Wextra -Werror

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
