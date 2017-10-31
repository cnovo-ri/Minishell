/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:22:52 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 23:46:55 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char	*cut_one(char *entry, char *tmp, t_sh *sh)
{
	int i;

	i = ft_strlen(entry);
	while (i > 0)
	{
		if (entry[i] == '/')
			break ;
		i--;
	}
	if (i == 0)
	{
		free(sh->pwd);
		if (!(sh->pwd = ft_strdup("/")))
			return (NULL);
		return (sh->pwd);
	}
	if (!(tmp = ft_strsub(entry, 0, i)))
		return (NULL);
	free(entry);
	return (tmp);
}

char	*chdir_ok(char *entry, char *init, t_sh *sh)
{
	sh->old_pwd = ft_strdup(init);
	sh->sh_env = modify_env(sh, "PWD", sh->pwd);
	sh->sh_env = modify_env(sh, "OLDPWD", init);
	ft_strdel(&init);
	return (entry);
}

char	*exec_cd(t_sh *sh)
{
	char	*init;
	char	*entry;
	int		i;

	i = 0;
	init = NULL;
	if (check_error(sh) == 0)
		return (sh->pwd);
	if (search_env(sh, "PWD") == -1)
		sh->sh_env = add_pwd_env(sh);
	if (!(sh = init_pwd(sh)))
		return (NULL);
	if (!(init = ft_strdup(sh->pwd)))
		return (NULL);
	sh->old_pwd = init;
	if (!(entry = add_pwd(sh, init)))
		return (sh->old_pwd);
	if (chdir(entry) == 0)
		return (chdir_ok(entry, init, sh));
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(sh->arg[1], 2);
	}
	return (sh->pwd);
}

void	exec(t_sh *sh, char *bin)
{
	pid_t	father;

	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
	{
		if (ft_strcmp(sh->arg[0], "emacs") == 0 ||
			ft_strcmp(sh->arg[0], "/usr/bin/emacs") == 0)
			execve(bin, sh->arg, sh->sh_env);
		else
			execve(bin, sh->arg, NULL);
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(bin, 2);
		free_sh(sh);
		exit(0);
	}
}

t_sh	*ls_tilt(t_sh *sh)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	tmp = NULL;
	i = search_env(sh, "HOME=");
	tmp = ft_strchr(sh->sh_env[i], '/');
	j = 0;
	k = sh->s_arg;
	while (j < k && sh->arg[j] != NULL)
	{
		if (sh->arg[j][0] == '~' && sh->arg[j][0] != '.')
		{
			free(sh->arg[j]);
			sh->arg[j] = ft_strdup(tmp);
		}
		j++;
	}
	return (sh);
}
