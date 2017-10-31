/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:37:52 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 23:40:10 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

int			help_builtin(t_sh *sh)
{
	if ((ft_strcmp(sh->arg[0], "setenv")) == 0)
	{
		if (!(sh->sh_env = set_env(sh)))
			return (-1);
		free_tab(sh->arg, sh->s_arg);
		sh->s_arg = 0;
		return (0);
	}
	else if ((ft_strcmp(sh->arg[0], "unsetenv")) == 0)
	{
		if (!(sh->sh_env = unset_env(sh)))
			return (-1);
		free_tab(sh->arg, sh->s_arg);
		sh->s_arg = 0;
		return (0);
	}
	return (1);
}

static void	put_error(t_sh *sh)
{
	ft_putstr_fd(sh->arg[0], 2);
	ft_putendl_fd(": command not found", 2);
}

t_sh		*help2_search_bin(t_sh *sh)
{
	int i;

	i = 0;
	if (sh->s_path > 0)
	{
		while (i < sh->s_path)
		{
			if (check_dir(sh->path[i], sh))
				break ;
			i++;
		}
		if (sh->path[i] != NULL)
			help_search_bin(sh, i);
		else
			put_error(sh);
		return (sh);
	}
	put_error(sh);
	return (sh);
}

t_sh		*search_bin(t_sh *sh)
{
	char			*tmp;
	char			*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (sh == NULL)
		exec(sh, sh->buf);
	if (!(sh->s_arg))
		return (sh);
	if (search_builtin(sh) == 0)
		return (sh);
	if (sh->arg[0][0] != '/' && sh->path)
		help2_search_bin(sh);
	else
	{
		exec(sh, sh->arg[0]);
		free_tab(sh->arg, sh->s_arg);
		sh->s_arg = 0;
		return (sh);
	}
	free_tab(sh->arg, sh->s_arg);
	sh->s_arg = 0;
	return (sh);
}
