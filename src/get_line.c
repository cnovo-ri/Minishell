/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:25:49 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 07:25:50 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

t_gl	*init_vars_gl(t_gl *gl)
{
	gl->i = 0;
	gl->a = 0;
	gl->j = 0;
	gl->k = 0;
	return (gl);
}

t_sh	*help_getline(t_sh *sh, t_gl *gl, char *buf)
{
	gl->i = 0;
	gl->j = 0;
	if (!(sh->arg = ft_char_2d(gl->a, ft_strlen(buf))))
		return (NULL);
	sh->s_arg = gl->a;
	while (gl->j != gl->a && buf[gl->i] != '\0' && buf[gl->i] != '\t')
	{
		gl->k = 0;
		while ((buf[gl->i] == ' ') || (buf[gl->i] == '\t'))
			gl->i++;
		while (buf[gl->i] != '\0' && buf[gl->i] != ' ' && buf[gl->i] != '\t' &&
				buf[gl->i] != '\n')
		{
			sh->arg[gl->j][gl->k] = buf[gl->i];
			gl->i++;
			gl->k++;
		}
		gl->j++;
	}
	return (sh);
}

t_gl	*help2_getline(t_gl *gl, char *buf)
{
	while ((buf[gl->i] == ' ') || (buf[gl->i] == '\t') || (buf[gl->i] == '\n'))
		gl->i++;
	while ((buf[gl->i] != ' ') && (buf[gl->i] != '\t') && (buf[gl->i] != '\0')
	&& (buf[gl->i] != '\n'))
	{
		if ((buf[gl->i + 1] == ' ') || (buf[gl->i + 1] == '\t')
			|| (buf[gl->i + 1] == '\0') || (buf[gl->i + 1] == '\n'))
		{
			gl->i++;
			gl->a++;
			break ;
		}
		return (gl);
	}
	return (gl);
}

t_sh	*get_line(char *buf, t_sh *sh)
{
	t_gl *gl;

	if (!(gl = (t_gl*)malloc(sizeof(t_gl))))
		return (NULL);
	gl = init_vars_gl(gl);
	while ((buf[gl->i] == ' ') || (buf[gl->i] == '\t') || (buf[gl->i] == '\n'))
		gl->i++;
	if (buf[gl->i] == '\0')
	{
		free(gl);
		return (sh);
	}
	while (buf[gl->i] != '\0')
	{
		gl = help2_getline(gl, buf);
		gl->i++;
	}
	sh = help_getline(sh, gl, buf);
	free(gl);
	return (sh);
}
