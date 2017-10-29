/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 02:41:38 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char	*cd_dot_cut(t_sh *sh)
{
	int i;
	int back;

	i = 0;
	back = count_back(sh->arg[1]);
	while (back > -1)
	{
		sh->arg[1] = cut_one_cut(sh->arg[1]);
		back--;
	}
	return (sh->arg[1]);
}

char	*check_slash(t_sh *sh, char *init)
{
	char**tab;
	int i;

	i = 0;
	if (sh->arg[1][0] == '/' && sh->arg[1][1] == '\0')
		return (sh->arg[1]);
	tab = ft_strsplit(sh->arg[1], '/');
	ft_strdel(&sh->arg[1]);
	if (tab[0] == NULL)
	{
		free(tab);
		sh->arg[1] = ft_strdup("/");
	}
	else
		sh->arg[1] = tab_to_1tab(tab, sh, init);
	return (sh->arg[1]);
}

int		check_2_moove(t_sh *sh)
{
	int	i;

	i = 0;
	while (sh->arg[1][i])
	{
		if (sh->arg[1][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**add_pwd_env(t_sh *sh)
{
	char	*tmp;
	char	buf[126];

	if (!(tmp = ft_strjoin("PWD=", getcwd(buf, 126))))
		return (NULL);
	sh->sh_env = modify_env(sh, "PWD", tmp);
	ft_strdel(&tmp);
	return (sh->sh_env);
}

t_sh	*init_pwd(t_sh *sh)
{
	int			i;
	char		*tmp;

	i = 0;
	while (i < sh->s_env)
	{
		if (ft_strncmp(sh->sh_env[i], "PWD=", 4) == 0)
		{
			if (!(tmp = ft_strsub(sh->sh_env[i], 4,
	(ft_strlen(sh->sh_env[i]) - 4))))
				return (NULL);
			ft_strdel(&sh->PWD);
			if (!(sh->PWD = ft_strdup(tmp)))
				return (NULL);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (sh);
}
