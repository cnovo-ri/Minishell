/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:37:31 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 22:19:43 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

int		check_dir(char *path, t_sh *sh)
{
	DIR				*rep;
	struct dirent	*ent;

	if (!(rep = opendir(path)))
		return (0);
	while ((ent = readdir(rep)))
	{
		if ((ft_strcmp(sh->arg[0], ent->d_name)) == 0)
		{
			closedir(rep);
			return (1);
		}
	}
	free(ent);
	closedir(rep);
	return (0);
}

int		help2_search_builtin(t_sh *sh)
{
	if ((ft_strcmp(sh->arg[0], "exit")) == 0)
	{
		free_sh(sh);
		exit(0);
	}
	else if ((ft_strcmp(sh->arg[0], "echo")) == 0)
	{
		ft_echo(sh);
		return (0);
	}
	else if ((ft_strcmp(sh->arg[0], "cd")) == 0)
	{
		if (!(sh->pwd = exec_cd(sh)))
			return (-1);
		return (0);
	}
	return (1);
}

int		help_search_builtin(t_sh *sh)
{
	if (help2_search_builtin(sh) == 0)
		return (0);
	else if ((ft_strcmp(sh->arg[0], "clear")) == 0)
	{
		ft_putstr("\033[H\033[2J");
		return (0);
	}
	else if (((ft_strcmp(sh->arg[0], "env")) == 0)
	|| ft_strcmp(sh->arg[0], "/usr/bin/env") == 0)
	{
		put_env(sh->sh_env, sh->s_env);
		free_tab(sh->arg, sh->s_arg);
		sh->s_arg = 0;
		return (0);
	}
	return (-1);
}

int		search_builtin(t_sh *sh)
{
	int i;

	i = 0;
	if (sh->arg[0] == NULL)
	{
		sh->s_arg = 0;
		return (0);
	}
	if (((i = help_search_builtin(sh)) == 0))
	{
		free_tab(sh->arg, sh->s_arg);
		sh->s_arg = 0;
		return (i);
	}
	if (help_builtin(sh) == 0)
		return (0);
	else if (ft_strcmp(sh->arg[0], "ls") == 0)
		return (-1);
	return (1);
}

void	help_search_bin(t_sh *sh, int i)
{
	char			*tmp;
	char			*tmp2;

	tmp = ft_strjoin("/", sh->arg[0]);
	tmp2 = ft_strjoin(sh->path[i], tmp);
	ft_strdel(&tmp);
	exec(sh, tmp2);
	ft_strdel(&tmp2);
}
