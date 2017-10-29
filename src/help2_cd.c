/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chelp2_cd.char                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 02:50:10 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

int		count_back(char	*name)
{
	int i;
	int slash;
	int back;

	i = 0;
	slash = 0;
	back = 0;
	while (name[i])
	{
		if (name[i] == '.' && name[i + 1] == '.')
			back++;
		i++;
	}
	return (back);
}

char	*give_value_old_pwd(t_sh *sh)
{
	sh->old_PWD = sh->PWD;
	return (sh->PWD);
}

char	*cd_dot(t_sh *sh, char *tmp)
{
	int back;

	back = count_back(sh->arg[1]);
	while (back > 0)
	{
		if (!(sh->PWD = cut_one(sh->PWD, tmp, sh)))
			return (NULL);
		ft_strdel(&tmp);
		back--;
	}
	return (sh->PWD);
}

int		no_arg(char *arg, t_sh *sh)
{
	int i;

	i = 0;
	while (i < sh->s_arg)
		if (arg[i++] != ' ')
			return (1);
	return (0);
}

int		test_racine(t_sh *sh)
{
	if (sh->arg[1][0] == '/' && sh->arg[1][1] == '\0')
		return (1);
	else if (sh->arg[1][0] == '/' && sh->arg[1][1] == '.'
	&& sh->arg[1][2] == '\0')
		return (1);
	else if (sh->arg[1][0] == '/' && sh->arg[1][1] == '.'
	&& sh->arg[1][2] == '.' && sh->arg[1][3] == '\0')
		return (1);
	return (0);
}
