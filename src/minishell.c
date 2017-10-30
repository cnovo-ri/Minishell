/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 23:39:08 by carmand           #+#    #+#             */
/*   Updated: 2017/10/29 22:38:48 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

static	void	print_prompt(t_sh *sh)
{
	ft_putstr("\033[32m");
	if (sh->PWD)
		ft_putstr(sh->PWD);
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
		if (sh->buf[1] == '\0')
			return (1);
		else
		{
			ls_tilt(sh);
			sh = search_bin(sh);
		}
	}
	return (1);
}
