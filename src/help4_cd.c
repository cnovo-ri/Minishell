/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help4_cd.char                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/19 02:24:26 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char	*add_pwd(t_sh *sh, char *init)
{
	char	*tmp;
	char	*tmp2;
	char 	*tmp3;

	tmp = NULL;
	if ((sh->arg[1] != NULL && sh->arg[1][0] != '-') && check_2_moove(sh) != 0)
	{
		if (sh->arg[1][0] == '.' && sh->arg[1] != NULL)
		{
			if (ft_strlen(sh->PWD) > 1)
			{
				sh->PWD = cd_dot(sh, tmp);
				return (sh->PWD);
			}
			give_value_old_pwd(sh);
			return (sh->PWD);
		}
		sh->arg[1] = check_slash(sh, init);
	}
	if (sh->s_arg == 1 || sh->arg[1][0] == '#' || sh->arg[1][0] == '~'
		|| sh->arg[1][0] == ';')
	{
		if (!(sh = go_home(sh)))
			return (NULL);
		return (sh->PWD);
	}
	else if (sh->arg[1][0] == '.' && sh->arg[1] != NULL)
	{
		if (ft_strlen(sh->PWD) > 1)
		{
			sh->PWD = cd_dot(sh, tmp);
			return (sh->PWD);
		}
		give_value_old_pwd(sh);
		return (sh->PWD);
	}
	else if (sh->arg[1][0] == '.' && sh->arg[1][1] == '\0')
		return (give_value_old_pwd(sh));
	else if (test_racine(sh) == 1)
	{
		ft_strdel(&sh->PWD);
		if (!(sh->PWD = ft_strdup("/")))
			return (NULL);
	}
	else if (sh->arg[1][0] == '-')
	{
		sh = go_old_pwd(sh);
		return (sh->PWD);
	}
	else
	{
		if (sh->arg[1][0] == '/' && sh->arg[1][1] != '\0')
		{
			ft_strdel(&sh->PWD);
			sh->PWD = ft_strdup(sh->arg[1]);
		}
		else
		{
			tmp2 = ft_strjoin(sh->PWD, "/");
			tmp3 = ft_strjoin(tmp2, sh->arg[1]);
			ft_strdel(&sh->PWD);
			if (!(sh->PWD = ft_strdup(tmp3)))
				return (NULL);
			ft_strdel(&tmp2);
			ft_strdel(&tmp3);
		}
	}
	return (sh->PWD);
}