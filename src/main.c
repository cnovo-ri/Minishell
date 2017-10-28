/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 23:39:08 by carmand           #+#    #+#             */
/*   Updated: 2017/10/27 11:57:54 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

t_sh *init_sh_first(t_sh *sh, char **env)
{
	int i;
	char *path;

	i = 0;
	path = NULL;
	sh->PWD = NULL;
	sh->PATH = NULL;
	sh->old_PWD = NULL;
	sh->sh_env = NULL;
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

int		search_noenv(t_sh *sh, char	**env, char *line)
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

t_sh *init_sh(t_sh *sh, char **env)
{
	int i;
	char *path;
	char	*tmp;

	i = 0;
	path = NULL;
	tmp = NULL;
	if (ft_strlen(sh->PWD) <= 0)
		return (sh);
	ft_strdel(&sh->PWD);
//	if (search_env(sh, "PATH=") == -1)
	//	modify_env(sh, "PATH", env[(search_noenv(sh, env, "PATH="))]);
	if (ft_strcmp(sh->buf, "\n") == 0/*ft_strchr(sh->buf, '\n')*/)
		{
	//		ft_putendl("OKOK");
			free_tab(sh->PATH, -1);
		//	sh->PWD = getcwd(tmp, 126);
		//	return (sh);
		}
	else if (sh->PATH[0] != '\0')
	{
//			ft_putendl("LALALA");
			free_tab(sh->arg, sh->s_arg);
			sh->s_arg = 0;
			free_tab(sh->PATH, sh->s_PATH);
	}
//	ft_putendl("LLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
	ft_strdel(&sh->old_PWD);
	while (i < sh->s_env)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			if (!(path = ft_strsub(env[i], 5, (ft_strlen(env[i]) - 5))))
				return (NULL);
			if (!(sh->PATH = get_path(path, sh)))
				return (NULL);
			free(path);
		}
		if (0 == ft_strncmp(env[i], "PWD=", 4))
		{
			if (!(tmp = ft_strsub(env[i], 4, (ft_strlen(env[i]) - 4))))
				return (NULL);
			if (!(sh->PWD = ft_strdup(tmp)))
				return (NULL);
			ft_strdel(&tmp);
		}
		i++;
	}
	sh->sh_env = env;
	return (sh);
}

int		main(int a, char **v, char **env)
{
	size_t ret;
	t_sh *sh;
	int	i;
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
	while(42)
	{
		if (!(sh = init_sh(sh, sh->sh_env)))
				return (0);
			ft_putstr("\033[32m");
			if (sh->PWD)
				ft_putstr(sh->PWD);
			ft_putstr("$> ");
			ft_putstr("\033[00m");
			i = 0;
/*			if (sh->s_arg > 0)
			{
				while (sh->arg[i])
				{
					printf("\nsh->arg[%d] : %s\n", i, sh->arg[i]);
					i++;
				}
			}
	*/		free_tab(sh->arg, sh->s_arg);
			if ((ret = read(0, sh->buf, 128)))
			{
				sh->buf[ret] = '\0';
				sh = get_line(sh->buf, sh);
				if (sh->buf[1] == '\0')
				{
					continue ;
				}
				else
				{
					ft_putendl("ELSE");
					sh = search_bin(sh);
				}
			}
	}
	a++;
	v[0][0] = 1;
	return (1);
}
