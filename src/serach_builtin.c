/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/30 00:02:07 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

t_sh	*search_bin(t_sh *sh)
{
	int				i;
	char			*tmp;
	char			*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (sh == NULL)
		exec(sh, sh->buf);
	if (sh->s_arg == 0)
		return (sh);
	if (search_builtin(sh) == 0)
		return (sh);
	if (sh->arg[0][0] != '/' && sh->PATH)
	{
		i = 0;
		while (i < sh->s_PATH)
		{
			if (check_dir(sh->PATH[i], sh))
				break ;
			i++;
		}
		if (sh->PATH[i] != NULL)
			help_search_bin(sh, i);
		else
		{
			ft_putstr_fd(sh->arg[0], 2);
			ft_putendl_fd(": command not found", 2);
		}
	}
	else
	{
		exec(sh, sh->arg[0]);
		return (sh);
	}
	free_tab(sh->arg, sh->s_arg);
	sh->s_arg = 0;
	return (sh);
}
