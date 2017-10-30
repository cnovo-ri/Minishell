/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:32:15 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 23:06:49 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char		**set_env(t_sh *sh)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	if (!(tmp = ft_strjoin(sh->arg[1], "=")))
		return (NULL);
	if (search_env(sh, tmp) > 0)
	{
		ft_strdel(&tmp);
		return (sh->sh_env);
	}
	else if (!(tmp2 = ft_strjoin(tmp, sh->arg[2])))
	{
		ft_strdel(&tmp);
		return (sh->sh_env);
	}
	if (ft_strncmp(sh->arg[1], "PATH", 4) == 0)
		sh->PATH = get_path(sh->arg[2], sh);
	ft_strdel(&tmp);
	sh->sh_env = realloc_env(sh, tmp2);
	ft_strdel(&tmp2);
	return (sh->sh_env);
}

static char	**help_unset_env(t_sh *sh, char **new, int j, int k)
{
	if (!(new = (char**)malloc(sizeof(char*) * (sh->s_env))))
		return (NULL);
	while (k != j)
	{
		if (!(new[k] = ft_strdup(sh->sh_env[k])))
			return (NULL);
		k++;
	}
	while (k != (sh->s_env - 1))
	{
		if (!(new[k] = ft_strdup(sh->sh_env[k + 1])))
			return (NULL);
		k++;
	}
	return (new);
}

char		**unset_env(t_sh *sh)
{
	int		i;
	int		j;
	int		k;
	char	**new;

	i = 0;
	j = -1;
	new = NULL;
	k = 0;
	if (sh->s_arg == 1)
		return (sh->sh_env);
	j = search_env(sh, sh->arg[1]);
	if (j == -1)
		return (sh->sh_env);
	else
		new = help_unset_env(sh, new, j, k);
	if (ft_strncmp(sh->arg[1], "PATH", 4) == 0)
		free_tab(sh->PATH, sh->s_PATH);
	free_tab(sh->sh_env, sh->s_env);
	sh->s_env--;
	return (new);
}
