/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 22:06:45 by carmand           #+#    #+#             */
/*   Updated: 2017/10/30 00:45:51 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

void	exec(t_sh *sh, char *bin)
{
	pid_t	father;

	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
	{
		if (ft_strcmp(sh->arg[0], "emacs") == 0 ||
			(ft_strcmp(sh->arg[0], "/usr/bin/emacs") == 0))
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
