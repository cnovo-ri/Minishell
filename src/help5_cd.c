/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help5_cd.c 	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/19 02:24:26 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

char	*cut_one_cut(char *name)
{
	int 	i;
	char 	*tmp;

	i = ft_strlen(name);
	while (i > 0)
	{
		if (name[i] == '/')
			break ;
		i--;
	}
	if (!(tmp = ft_strsub(name, 0, i)))
		return (NULL);
	ft_strdel(&name);
	return (tmp);
}