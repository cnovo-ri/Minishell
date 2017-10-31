/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 00:05:49 by ttresori          #+#    #+#             */
/*   Updated: 2017/08/29 19:05:50 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		help_g(int fd, t_gnl *g, char ***line)
{
	if (g->ret < 0)
		return (-1);
	if (ft_strlen(g->t) > 0)
	{
		**line = g->t;
		ft_strdel(&g->rest[fd]);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	g;

	if (fd < 0 || !line || fd < 3)
		return (-1);
	if (!(g.rest[fd]))
		g.rest[fd] = ft_strnew(BUFF_SIZE);
	g.t = ft_strncpy(ft_strnew(BUFF_SIZE), g.rest[fd], BUFF_SIZE);
	while (!(ft_strchr(g.t, '\n')))
	{
		g.ret = read(fd, g.buf, BUFF_SIZE);
		g.buf[g.ret] = '\0';
		g.cpy = ft_strjoin(g.t, g.buf);
		ft_strdel(&g.t);
		g.t = g.cpy;
		if (g.ret < 1)
			return (help_g(fd, &g, &line));
	}
	g.rest[fd] = ft_strncpy(g.rest[fd], (ft_strchr(g.t, '\n') + 1), BUFF_SIZE);
	*line = ft_strsub(g.t, 0, (ft_strlen(g.t) - ft_strlen(ft_strchr(g.t, 10))));
	return (1);
}
