/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help3_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:29:59 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 07:30:01 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char	*help_one(t_sh *sh, char **tab, t_cp *cp)
{
	char *tmp;

	tmp = ft_strjoin("/", cp->arg);
	ft_strdel(&cp->arg);
	sh->arg[1] = ft_strsub(tmp, 0, (ft_strlen(tmp) - 1));
	ft_strdel(&tmp);
	free_tab(tab, cp->i);
	return (sh->arg[1]);
}

void	help_while_tab(t_cp *cp, char **tab)
{
	while (tab[cp->i])
	{
		while (tab[cp->i][cp->k])
		{
			if (tab[cp->i][cp->k + 1] == '\0')
			{
				cp->arg[cp->c] = tab[cp->i][cp->k];
				cp->c++;
				cp->arg[cp->c] = '/';
				cp->c++;
				break ;
			}
			else
			{
				cp->arg[cp->c] = tab[cp->i][cp->k];
				cp->k++;
				cp->c++;
			}
		}
		cp->k = 0;
		cp->i++;
	}
	cp->arg[cp->c] = '\0';
}

t_cp	*init_vars_cp(t_cp *cp)
{
	cp->i = 0;
	cp->k = 0;
	cp->size = 0;
	cp->c = 0;
	cp->tmp = NULL;
	cp->arg = NULL;
	return (cp);
}

char	*tab_to_1tab(char **tab, t_sh *sh, char *init)
{
	t_cp *cp;

	if (!(cp = (t_cp*)malloc(sizeof(t_cp))))
		return (0);
	cp = init_vars_cp(cp);
	while (tab[cp->i])
	{
		cp->size = (ft_strlen(tab[cp->i]) + cp->size);
		cp->i++;
	}
	cp->arg = ft_strnew(cp->size + cp->i);
	cp->i = 0;
	help_while_tab(cp, tab);
	sh->arg[1] = help_one(sh, tab, cp);
	if (ft_strchr(sh->arg[1], '.') != NULL)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(sh->arg[1], 2);
		ft_strdel(&sh->arg[1]);
		sh->arg[1] = ft_strdup(init);
		free(cp);
		return (sh->arg[1]);
	}
	free(cp);
	return (sh->arg[1]);
}
