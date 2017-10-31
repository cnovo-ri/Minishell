/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help5_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:31:06 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/31 02:50:05 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char			*cut_one_cut(char *name)
{
	int		i;
	char	*tmp;

	i = ft_strlen(name);
	while (i > 0)
	{
		if (name[i] == '/')
			break ;
		i--;
	}
	if (!(tmp = ft_strsub(name, 0, i)))
		return (NULL);
	ft_strdel(&name);
	return (tmp);
}

static void		free_var(t_sh *sh, char *tmp)
{
	ft_strdel(&sh->pwd);
	sh->pwd = ft_strdup(tmp);
	ft_putendl(sh->old_pwd);
	ft_strdel(&tmp);
}

t_sh			*go_old_pwd(t_sh *sh)
{
	int		i;
	int		i2;
	char	*tmp;
	int		find;

	i = 0;
	i2 = 0;
	find = search_env(sh, "OLDPWD=");
	if (find == -1)
	{
		if (!(tmp = ft_strjoin("OLDPWD=", sh->old_pwd)))
			return (NULL);
		sh->sh_env = modify_env(sh, "OLDPWD=", tmp);
		ft_strdel(&sh->old_pwd);
	}
	else
	{
		if (!(tmp = ft_strsub(sh->sh_env[find], 7,
	ft_strlen(sh->sh_env[find]))))
			return (NULL);
	}
	free_var(sh, tmp);
	return (sh);
}

t_sh			*go_home(t_sh *sh)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (i < sh->s_env)
	{
		if (ft_strncmp("HOME=", sh->sh_env[i], 5) == 0)
		{
			if (!(tmp = ft_strsub(sh->sh_env[i], 5,
	(ft_strlen(sh->sh_env[i]) - 5))))
				return (NULL);
			ft_strdel(&sh->pwd);
			sh->pwd = ft_strdup(tmp);
			give_value_old_pwd(sh);
			ft_strdel(&tmp);
			return (sh);
		}
		i++;
	}
	return (sh);
}

int				check_error(t_sh *sh)
{
	if (sh->s_arg == 3)
	{
		ft_putstr_fd("cd: string in pwd: ", 2);
		ft_putendl_fd(sh->arg[1], 2);
		return (0);
	}
	else if (sh->s_arg > 3)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (0);
	}
	return (1);
}
