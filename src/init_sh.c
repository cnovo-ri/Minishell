/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sh.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 23:39:08 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 21:30:44 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

t_sh  *sh_init_var(t_sh *sh)
{
    sh->PWD = NULL;
    sh->PATH = NULL;
    sh->old_PWD = NULL;
    sh->sh_env = NULL;
    return (sh);
}

t_sh	*init_sh_first(t_sh *sh, char **env)
{
	int 	i;
	char	*path;

	i = 0;
	path = NULL;
  sh = sh_init_var(sh);
	while (env[i] != NULL)
	{
		if (0 == ft_strncmp(env[i], "PATH=", 5))
		{
			if (!(path = ft_strsub(env[i], 5, (ft_strlen(env[i]) - 5))))
				return (NULL);
			if (!(sh->PATH = get_path(path, sh)))
				return (NULL);
			ft_strdel(&path);
		}
		if (0 == ft_strncmp(env[i], "PWD=", 4))
		{
			if (!(sh->PWD = ft_strsub(env[i], 4, (ft_strlen(env[i]) - 4))))
				return (NULL);
		}
		i++;
	}
	if (!(sh->sh_env = (char**)malloc(sizeof(char*) * i)))
		return (NULL);
	sh->s_env = i;
	i = 0;
	while (i < sh->s_env)
	{
		if (!(sh->sh_env[i] = ft_strdup(env[i])))
			return (NULL);
		i++;
	}
	sh->sh_env = modify_env(sh, "OLDPWD", sh->PWD);
	return (sh);
}
