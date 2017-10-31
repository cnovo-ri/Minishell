/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:33:16 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 07:33:19 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

void	put_env(char **sh_env, int s_env)
{
	int	i;

	i = 0;
	while (i < s_env)
	{
		ft_putendl(sh_env[i]);
		i++;
	}
}

int		search_env(t_sh *sh, char *line)
{
	int i;

	i = 0;
	while (i < sh->s_env)
	{
		if (ft_strncmp(sh->sh_env[i], line, ft_strlen(line)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strlen_2d(t_sh *sh)
{
	int i;

	i = 0;
	while (i < sh->s_env)
		i++;
	return (i);
}

char	**ft_cpy_2char(t_sh *sh, char **init)
{
	int i;

	i = 0;
	if (!(sh->sh_env = (char**)malloc(sizeof(char*) * sh->s_env)))
		return (init);
	while (i < sh->s_env)
	{
		sh->sh_env[i] = ft_strdup(init[i]);
		i++;
	}
	free_tab(init, sh->s_env);
	return (sh->sh_env);
}

char	**realloc_env(t_sh *sh, char *place)
{
	char	**new;
	char	*tmp;
	int		start;

	start = 0;
	if (!(new = (char**)malloc(sizeof(char*) * (sh->s_env + 1))))
		return (NULL);
	tmp = ft_strdup(place);
	while (start < sh->s_env)
	{
		new[start] = ft_strdup(sh->sh_env[start]);
		start++;
	}
	new[start] = ft_strdup(tmp);
	ft_strdel(&tmp);
	if (start > 0)
		free_tab(sh->sh_env, sh->s_env);
	sh->s_env = sh->s_env + 1;
	sh->sh_env = ft_cpy_2char(sh, new);
	return (sh->sh_env);
}
