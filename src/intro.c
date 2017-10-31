/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnovo-ri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 07:33:49 by cnovo-ri          #+#    #+#             */
/*   Updated: 2017/10/30 07:33:51 by cnovo-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

static void	intro_4(void)
{
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||\033[32mn\033[00m");
	ft_putstr(" |||\033[32mi\033[00m |||\033[32ms\033[00m |||");
	ft_putstr("\033[32mh\033[00m |||\033[32me\033[00m |||\033[32ml\033[00m");
	ft_putendl(" |||  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||\033[32mn\033[00m");
	ft_putstr(" |||\033[32mi\033[00m |||\033[32ms\033[00m |||");
	ft_putstr("\033[32mh\033[00m |||\033[32me\033[00m |||\033[32ml\033[00m");
	ft_putendl(" |||\033[32ml\033[00m ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	ft_putendl("\n");
}

static void	intro_3(void)
{
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||\033[32mn\033[00m");
	ft_putstr(" |||\033[32mi\033[00m |||\033[32ms\033[00m |||");
	ft_putendl("\033[32mh\033[00m |||  |||  |||  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||\033[32mn\033[00m");
	ft_putstr(" |||\033[32mi\033[00m |||\033[32ms\033[00m |||");
	ft_putendl("\033[32mh\033[00m |||\033[32me\033[00m |||  |||  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	intro_4();
}

static void	intro_2(void)
{
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||\033[32mn\033[00m");
	ft_putendl(" |||  |||  |||  |||  |||  |||  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||\033[32mn\033[00m");
	ft_putendl(" |||\033[32mi\033[00m |||  |||  |||  |||  |||  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||\033[32mn\033[00m");
	ft_putstr(" |||\033[32mi\033[00m |||\033[32ms\033[00m |||  |||  |||  ||| ");
	ft_putendl(" ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	intro_3();
}

void		intro(void)
{
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putendl(" ||  |||  |||  |||  |||  |||  |||  |||  |||  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||  |||  |||  |||  |||  |||  |||  ||");
	ft_putendl("|  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	usleep(200000);
	ft_putstr("\033[H\033[2J");
	ft_putendl("  ____ ____ ____ ____ ____ ____ ____ ____ ____ ");
	ft_putstr(" ||\033[32mM\033[00m |||\033[32mi\033[00m |||  |||  ");
	ft_putendl("|||  |||  |||  |||  |||  ||");
	ft_putendl(" ||__|||__|||__|||__|||__|||__|||__|||__|||__||");
	ft_putendl(" |/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|/__\\|");
	intro_2();
}
