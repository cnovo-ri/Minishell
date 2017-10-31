/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:34:15 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 23:52:03 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

int		search_noenv(t_sh *sh, char **env, char *line)
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
	tmp = NULL;
	if (ft_strcmp(sh->buf, "\n") == 0)
		return (sh);
	return (sh);
}

char	*init_cmp(t_sh *sh, char *tmp, char **env, int i)
{
	if (!(tmp = ft_strsub(env[i], 4, (ft_strlen(env[i]) - 4))))
		return (NULL);
	if (!(sh->pwd = ft_strdup(tmp)))
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
	if (ft_strlen(sh->pwd) <= 0)
		return (sh);
	ft_strdel(&sh->pwd);
	help_init_sh(sh, tmp);
	ft_strdel(&tmp);
	ft_strdel(&sh->old_pwd);
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
	if (!(env[0]))
	{
		ft_putendl_fd("error : env is missing", 2);
		free(sh);
		exit(EXIT_FAILURE);
	}
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
