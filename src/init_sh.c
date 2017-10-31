/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:33:59 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/31 02:51:04 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

t_sh			*sh_init_var(t_sh *sh)
{
	sh->pwd = NULL;
	sh->path = NULL;
	sh->old_pwd = NULL;
	sh->sh_env = NULL;
	return (sh);
}

t_sh			*init_sh_first_help(t_sh *sh, char **env, int i, char *path)
{
	if (0 == ft_strncmp(env[i], "PATH=", 5))
	{
		if (!(path = ft_strsub(env[i], 5, (ft_strlen(env[i]) - 5))))
			return (NULL);
		if (!(sh->path = get_path(path, sh)))
			return (NULL);
		ft_strdel(&path);
	}
	if (0 == ft_strncmp(env[i], "PWD=", 4))
	{
		if (!(sh->pwd = ft_strsub(env[i], 4,
	(ft_strlen(env[i]) - 4))))
			return (NULL);
	}
	return (sh);
}

t_sh			*init_sh_first(t_sh *sh, char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	sh = sh_init_var(sh);
	while (env[i] != NULL)
		sh = init_sh_first_help(sh, env, i++, path);
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
	sh->sh_env = modify_env(sh, "OLDPWD", sh->pwd);
	return (sh);
}

static	void	print_prompt(t_sh *sh)
{
	ft_putstr("\033[32m");
	if (sh->pwd)
		ft_putstr(sh->pwd);
	ft_putstr("$> ");
	ft_putstr("\033[00m");
}

int				minishell(t_sh *sh)
{
	int		i;
	size_t	ret;

	i = 0;
	ret = 0;
	if (!(sh = init_sh(sh, sh->sh_env)))
		return (-1);
	print_prompt(sh);
	i = 0;
	if ((ret = read(0, sh->buf, 128)))
	{
		sh->buf[ret] = '\0';
		sh = get_line(sh->buf, sh);
		if (sh->buf[1] == '\0' || sh->s_arg <= 0)
			return (1);
		else
		{
			ls_tilt(sh);
			sh = search_bin(sh);
		}
	}
	return (1);
}
