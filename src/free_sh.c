/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmand <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 00:23:47 by carmand           #+#    #+#             */
/*   Updated: 2017/10/27 11:30:26 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

void		free_tab(char **tab, int len)
{
	int	i;

	i = 0;
	if (tab != NULL && len != -1 && len > 1)
	{
		while (i < len)
		{
/*			ft_putchar('\n');
			ft_putendl("LE FREE");
*/			if (tab[i][0] != '\0')
				ft_strdel(&tab[i]);
//			ft_putendl("PAS FREE");
			i++;
		}
		ft_putendl("LE FREE");
		free(tab);
	}
}

void		free_sh(t_sh *sh)
{
	free_tab(sh->sh_env, sh->s_env);
	free_tab(sh->PATH, sh->s_PATH);
	free_tab(sh->arg, sh->s_arg);
	ft_strdel(&sh->PWD);
	ft_strdel(&sh->old_PWD);
	ft_strdel(&sh->buf);
	free(sh);
}
