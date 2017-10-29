/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:32:15 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 02:05:54 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char			**modify_env(t_sh *sh, char *line, char *modify)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (line == NULL)
		return ((sh->sh_env = realloc_env(sh, modify)));
	if (!(tmp2 = ft_strjoin(line, "=")))
		return (NULL);
	if (!(tmp = ft_strjoin(tmp2, modify)))
		return (NULL);
	if ((i = search_env(sh, line)) != -1)
	{
		ft_strdel(&sh->sh_env[i]);
		sh->sh_env[i] = ft_strdup(tmp);
	}
	else
	{
		if (!(sh->sh_env = realloc_env(sh, modify)))
			return (NULL);
	}
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (sh->sh_env);
}

static	char	**help_add_env(t_sh *sh, char *tmp, char *tmp2)
{
	int		s;
	int		j;
	char	**new;

	s = 0;
	j = 0;
	new = NULL;
	while (sh->sh_env[j] != NULL)
		j++;
	if (!(new = (char**)malloc(sizeof(char*) * (j + 2))))
		return (NULL);
	while (s++ < j)
		if (!(new[s] = ft_strdup(sh->sh_env[s])))
			return (NULL);
	if (!(tmp = ft_strjoin(sh->arg[1], "=")))
		return (NULL);
	if (!(tmp2 = ft_strjoin(tmp, sh->arg[2])))
		return (NULL);
	if (!(new[s] = ft_strdup(tmp2)))
		return (NULL);
	new[s + 1] = NULL;
	sh->sh_env = NULL;
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (new);
}

char			**add_env(t_sh *sh, int i)
{
	char	**new;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (i == -1)
	{
		new = help_add_env(sh, tmp, tmp2);
		return (new);
	}
	else
	{
		new = NULL;
		if (!(tmp = ft_strjoin(sh->arg[1], "=")))
			return (NULL);
		if (!(tmp2 = ft_strjoin(tmp, sh->arg[2])))
			return (NULL);
		if (!(sh->sh_env[i] = ft_strdup(tmp2)))
			return (NULL);
		sh->sh_env = realloc_env(sh, tmp2);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (sh->sh_env);
}
