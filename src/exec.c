/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 22:06:45 by carmand           #+#    #+#             */
/*   Updated: 2017/10/18 04:00:47 by carmand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

void	exec(t_sh *sh, char *bin)
{
	pid_t 	father;

	father = fork();
	if (father > 0)
		wait (0);
	if (father == 0)
	{
		execve(bin, sh->arg, sh->sh_env);
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(bin, 2);
		free_sh(sh);
		exit (0);
	}
}
