/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 23:39:08 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 22:36:58 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

int		search_noenv(t_sh *sh, char**env, char	*line)
{
	int i;

	i = 0;
	while (i < sh->s_env)
	{
		if (ft_strncmp(env[i], line, ft_strlen(line)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

t_sh	*help_init_sh(t_sh *sh, char *tmp)
{
	if (ft_strcmp(sh->buf, "\n") == 0)
	{
		free_tab(sh->PATH, -1);
		sh->PWD = getcwd(tmp, 126);
		return (sh);
	}
	return (sh);
}

char	*init_cmp(t_sh *sh, char *tmp, char **env, int i)
{
	if (!(tmp = ft_strsub(env[i], 4, (ft_strlen(env[i]) - 4))))
		return (NULL);
	if (!(sh->PWD = ft_strdup(tmp)))
		return (NULL);
	ft_strdel(&tmp);
	return (tmp);
}

t_sh	*init_sh(t_sh *sh, char **env)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	path = NULL;
	tmp = NULL;
	if (ft_strlen(sh->PWD) <= 0)
		return (sh);
	ft_strdel(&sh->PWD);
	help_init_sh(sh, tmp);
	ft_strdel(&sh->old_PWD);
	while (i < sh->s_env)
	{
		if (0 == ft_strncmp(env[i], "PWD=", 4))
			tmp = init_cmp(sh, tmp, env, i);
		i++;
	}
	sh->sh_env = env;
	return (sh);
}

int		main(int a, char **v, char **env)
{
	t_sh	*sh;

	sh = NULL;
	if (!(sh = (t_sh*)malloc(sizeof(t_sh))))
		return (0);
	sh->sh_env = NULL;
	if (!(sh = init_sh_first(sh, env)))
		return (0);
	sh->buf = NULL;
	sh->buf = ft_strnew(128);
	sh->arg = NULL;
	intro();
	while (42)
		if (minishell(sh) == -1)
			break ;
	a++;
	v[0][0] = 1;
	return (1);
}
