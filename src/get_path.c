/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:26:02 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 07:26:42 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

static char	**help_getpath(char *buf, t_gl *gl, char **path, t_sh *sh)
{
	gl->i = 0;
	gl->j = 0;
	if (!(path = ft_char_2d(gl->a, ft_strlen(buf))))
		return (NULL);
	sh->s_path = gl->a;
	while (gl->j != gl->a && buf[gl->i] != '\0')
	{
		gl->k = 0;
		while (buf[gl->i] == ':')
			gl->i++;
		while (buf[gl->i] != '\0' && buf[gl->i] != ':' && buf[gl->i] != '\n')
		{
			path[gl->j][gl->k] = buf[gl->i];
			gl->i++;
			gl->k++;
		}
		gl->j++;
	}
	return (path);
}

static void	help2_getpath(char *buf, t_gl *gl)
{
	while (buf[gl->i] != '\0')
	{
		if (buf[gl->i] == ':')
		{
			while (buf[gl->i + 1] == ':')
				gl->i++;
			if (buf[gl->i + 1] != '\0')
				gl->a++;
			else
				break ;
		}
		gl->i++;
	}
}

char		**get_path(char *buf, t_sh *sh)
{
	char	**path;
	t_gl	*gl;

	if (!(gl = (t_gl*)malloc(sizeof(t_gl))))
		return (NULL);
	path = NULL;
	gl = init_vars_gl(gl);
	gl->a = 1;
	while (buf[gl->i] == ':')
		gl->i++;
	if (buf[gl->i] == '\0')
		return (NULL);
	help2_getpath(buf, gl);
	path = help_getpath(buf, gl, path, sh);
	free(gl);
	return (path);
}

void		free_tab(char **tab, int len)
{
	int	i;

	i = 0;
	if (tab != NULL && len != -1 && len > 0 && tab[0] != NULL)
	{
		while (i < len)
		{
			if (tab[i][0] != '\0')
				ft_strdel(&tab[i]);
			i++;
		}
		free(tab);
		len = 0;
	}
}

void		free_sh(t_sh *sh)
{
	free_tab(sh->sh_env, sh->s_env);
	free_tab(sh->arg, sh->s_arg);
	free_tab(sh->path, sh->s_path);
	ft_strdel(&sh->pwd);
	ft_strdel(&sh->old_pwd);
	ft_strdel(&sh->buf);
	free(sh);
}
