/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help4_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:30:24 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/31 02:56:54 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

static char		*help_add_pwd(t_sh *sh, char *tmp, char *init)
{
	tmp = NULL;
	if ((sh->arg[1] != NULL && sh->arg[1][0] != '-') && check_2_moove(sh) != 0)
	{
		if (sh->arg[1][0] == '.' && sh->arg[1] != NULL)
		{
			give_value_old_pwd(sh);
			return (sh->pwd);
		}
		sh->arg[1] = check_slash(sh, init);
	}
	return (sh->pwd);
}

static int		help2_add_pwd(t_sh *sh, char *tmp)
{
	if (sh->s_arg == 1 || sh->arg[1][0] == '#' || sh->arg[1][0] == '~'
		|| sh->arg[1][0] == ';')
	{
		if (!(sh = go_home(sh)))
			return (-1);
		return (1);
	}
	else if (sh->arg[1][0] == '.' && sh->arg[1] != NULL)
	{
		if (ft_strlen(sh->pwd) > 1)
		{
			sh->pwd = cd_dot(sh, tmp);
			return (1);
		}
		sh->pwd = give_value_old_pwd(sh);
		return (1);
	}
	return (0);
}

static void		help3_add_pwd(char *tmp2, char *tmp3, t_sh *sh)
{
	if (sh->arg[1][0] == '/' && sh->arg[1][1] != '\0')
	{
		ft_strdel(&sh->pwd);
		sh->pwd = ft_strdup(sh->arg[1]);
	}
	else
	{
		tmp2 = ft_strjoin(sh->pwd, "/");
		tmp3 = ft_strjoin(tmp2, sh->arg[1]);
		ft_strdel(&sh->pwd);
		if (!(sh->pwd = ft_strdup(tmp3)))
			return ;
		ft_strdel(&tmp2);
		ft_strdel(&tmp3);
	}
}

char			*add_pwd(t_sh *sh, char *init)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	help_add_pwd(sh, tmp, init);
	if (help2_add_pwd(sh, tmp) == 1)
		return (sh->pwd);
	else if (test_racine(sh) == 1)
	{
		ft_strdel(&sh->pwd);
		if (!(sh->pwd = ft_strdup("/")))
			return (NULL);
	}
	else if (sh->arg[1][0] == '-' && sh->arg[1][1] == '\0')
	{
		sh = go_old_pwd(sh);
		return (sh->pwd);
	}
	else
		help3_add_pwd(tmp2, tmp3, sh);
	return (sh->pwd);
}
