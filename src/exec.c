/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 22:06:45 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 03:33:16 by cnovo-ri         ###   ########.fr       */
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
		execve(bin, sh->arg, NULL);
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(bin, 2);
		free_sh(sh);
		exit(0);
	}
}
/*
static int		tablen(char **tab)
{
	int i;

	i = 0;
	if (!(tab))
		return (0);
	while (tab[i])
		i++;
	return (i);
}
*/

t_sh		*ls_tilt(t_sh *sh)
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
	while (sh->arg && j < k && sh->arg[j] != NULL)
	{
		if (sh->arg[j][0] == '~' && sh->arg[j][0] != '.')
		{
			free(sh->arg[j]);
//			ft_putendl("one");
			sh->arg[j] = ft_strdup(tmp);
//			ft_putendl("two");
		}
			//str_swap(&sh->arg[j], &tmp);
		j++;
	}
//	free(tmp);
	return (sh);
}
