/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 02:12:26 by ttresori         ###   ########.fr       */
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
		free(sh->PWD);
		if (!(sh->PWD = ft_strdup("/")))
			return (NULL);
		return (sh->PWD);
	}
	if (!(tmp = ft_strsub(entry, 0, i)))
		return (NULL);
	free(entry);
	return (tmp);
}

char	*chdir_ok(char *entry, char *init, t_sh *sh)
{
	sh->old_PWD = ft_strdup(init);
	sh->sh_env = modify_env(sh, "PWD", sh->PWD);
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
		return (sh->PWD);
	if (search_env(sh, "PWD") == -1)
		sh->sh_env = add_pwd_env(sh);
	if (!(sh = init_pwd(sh)))
		return (NULL);
	if (!(init = ft_strdup(sh->PWD)))
		return (NULL);
	sh->old_PWD = init;
	if (!(entry = add_pwd(sh, init)))
		return (sh->old_PWD);
	if (chdir(entry) == 0)
		return (chdir_ok(entry, init, sh));
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(sh->arg[1], 2);
	}
	return (sh->PWD);
}
