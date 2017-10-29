/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_minishell.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 02:30:06 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 03:19:58 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_MINISHELL_H
# define LIB_MINISHELL_H

# include "../libft/libft.h"
# include <sys/wait.h>
# include "sys/stat.h"
# include <dirent.h>
# include <unistd.h>
#include <curses.h>

# define IS_SPACE(x) (x == ' ' || x == '\t' || x == '\r' || x  == '\f')

typedef struct s_sh
{
	char 	**arg;
	int		s_arg;
	char 	**PATH;
	int		s_PATH;
	char 	*old_PWD;
	char 	*PWD;
	char 	**sh_env;
	int		s_env;
	char	*buf;
}				t_sh;

t_sh	*ls_tilt(t_sh *sh);
void	intro(void);
t_sh	*get_line(char *buf, t_sh *sh);
char    **get_path(char *buf, t_sh *sh);
char    **set_env(t_sh *sh);
char	**unset_env(t_sh *sh);
void    exec(t_sh *sh, char *bin);
t_sh    *search_bin(t_sh *sh);
void    put_env(char **sh_env, int s_env);
char 	*exec_cd(t_sh *sh);
void	ft_echo(t_sh *sh);
t_sh	*init_sh(t_sh *sh, char **env);
t_sh 	*init_pwd(t_sh *sh);
char	*add_pwd(t_sh *sh, char *init);
char	**add_pwd_env(t_sh *sh);
char	**update_env(t_sh *sh);
char	*cut_one(char *entry, char *tmp, t_sh *sh);
t_sh	*go_home(t_sh *sh);
t_sh 	*go_old_pwd(t_sh *sh);
char	**modify_env(t_sh *sh, char *line, char *modify);
char 	**realloc_env(t_sh *sh, char *modify);
int		search_env(t_sh *sh, char *line);
void	free_tab(char **tab, int len);
void	free_sh(t_sh *sh);
void	exec_prout(t_sh *sh, char *bin);
char	*give_value_old_pwd(t_sh *sh);
char	**add_env(t_sh *sh, int i);
int		count_back(char	*name);
char	*cd_dot(t_sh *sh, char *tmp);
int		test_racine(t_sh *sh);
char	*tab_to_1tab(char **tab, t_sh *sh, char *init);
char	*add_pwd(t_sh *sh, char *init);
char	*check_slash(t_sh *sh, char *init);
int		check_2_moove(t_sh *sh);
char	*cut_one_cut(char *name);
int		check_error(t_sh *sh);

#endif
