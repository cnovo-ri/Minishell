/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help3_cd.c  	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 21:26:24 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char	*help_one(char *tmp, char *arg, t_sh *sh, char **tab, int i)
{
	tmp = ft_strjoin("/", arg);
	ft_strdel(&arg);
	sh->arg[1] = ft_strsub(tmp, 0, (ft_strlen(tmp) - 1));
	ft_strdel(&tmp);
	free_tab(tab, i);
	return (sh->arg[1]);
}

char	*tab_to_1tab(char **tab, t_sh *sh, char *init)
{
	int		i;
	int		k;
	int		c;
	int 	size;
	char	*tmp;
	char	*arg;

	i = 0;
	k = 0;
	size = 0;
	c = 0;
	tmp = NULL;
	arg = NULL;
	while (tab[i])
	{
		size = (ft_strlen(tab[i]) + size);
		i++;
	}
	arg = ft_strnew(size + i);
	i = 0;
	while (tab[i])
	{
		while (tab[i][k])
		{
			if (tab[i][k + 1] == '\0')
			{
				arg[c] = tab[i][k];
				c++;
				arg[c] = '/';
				c++;
				break ;
			}
			else
			{
				arg[c] = tab[i][k];
				k++;
				c++;
			}
		}
		k = 0;
		i++;
	}
	arg[c] = '\0';
	sh->arg[1] = help_one(tmp, arg, sh, tab, i);
	if (ft_strchr(sh->arg[1], '.') != NULL)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(sh->arg[1], 2);
		ft_strdel(&sh->arg[1]);
		sh->arg[1] = ft_strdup(init);
		return (sh->arg[1]);
	}
	return (sh->arg[1]);
}
