/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 21:23:54 by carmand           #+#    #+#             */
/*   Updated: 2017/10/19 02:24:26 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

int	count_back(char	*name)
{
	int i;
	int slash;
	int back;

	i = 0;
	back = 0;
	slash = 0;
	while(name[i])
	{
		if (name[i] == '.' && name[i + 1] == '.')
			back++;
		i++;
	}
	return(back);
}

char	*give_value_old_pwd(t_sh *sh)
{
	sh->old_PWD = sh->PWD;
	return(sh->PWD);
}

char *cd_dot(t_sh *sh, char *tmp)
{
	int back;

	back = count_back(sh->arg[1]);
	while(back > 0)
	{
		if (!(sh->PWD = cut_one(sh->PWD, tmp, sh)))
			return (NULL);
		ft_strdel(&tmp);
		back--;
	}
	return (sh->PWD);
}

int no_arg(char *arg, t_sh *sh)
{
	int i;

	i = 0;
	while(i < sh->s_arg)
		if (arg[i++] != ' ')
			return(1);
	return(0);
}

int	test_racine(t_sh *sh)
{
	if (sh->arg[1][0] == '/' && sh->arg[1][1] == '\0')
		return (1);
	else if (sh->arg[1][0] == '/' && sh->arg[1][1] == '.' && sh->arg[1][2] == '\0')
		return (1);
	else if (sh->arg[1][0] == '/' && sh->arg[1][1] == '.' && sh->arg[1][2] == '.'
		&& sh->arg[1][3] == '\0')
		return (1);
	return (0);
}

char	*cut_one_cut(char *name)
{
	int i;
	char *tmp;

	i = ft_strlen(name);
	while (i > 0)
	{
		if (name[i] == '/')
			break;
		i--;
	}
	if (!(tmp = ft_strsub(name, 0, i)))
		return (NULL);
	ft_strdel(&name);
	return(tmp);
}

char	*cd_dot_cut(t_sh *sh)
{
	int i;
	int back;

	i = 0;
	back = count_back(sh->arg[1]);
	while(back > -1)
	{
		sh->arg[1] = cut_one_cut(sh->arg[1]);
		back--;
	}
	return (sh->arg[1]);
}

char	*tab_to_1tab(char	**tab, t_sh *sh, char *init)
{
	int 	i;
	int		k;
	int		c;
	int 	size;
	char	*tmp;
	char	*arg;

	i = 0;
	k = 0;
	size = 0;
	c = 0;
	while(tab[i])
	{
		size = (ft_strlen(tab[i]) + size);
		i++;
	}
	arg = ft_strnew(size + i);
	i = 0;
	while(tab[i])
	{
		while(tab[i][k])
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
	tmp = ft_strjoin("/", arg);
	ft_strdel(&arg);
	sh->arg[1] = ft_strsub(tmp, 0, (ft_strlen(tmp) - 1));
	ft_strdel(&tmp);
	free_tab(tab, i);
	if (ft_strchr(sh->arg[1], '.') != NULL)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(sh->arg[1], 2);
		ft_strdel(&sh->arg[1]);
		sh->arg[1] = ft_strdup(init);
		return(sh->arg[1]);
	}
	return (sh->arg[1]);
}

char	*check_slash(t_sh *sh, char *init)
{
	char	**tab;
	int i;

	i = 0;
	if (sh->arg[1][0] == '/' && sh->arg[1][1] == '\0')
		return (sh->arg[1]);
	tab = ft_strsplit(sh->arg[1], '/');
	ft_strdel(&sh->arg[1]);
	if (tab[0] == NULL)
	{
		free(tab);
		sh->arg[1] = ft_strdup("/");
	}
	else
		sh->arg[1] = tab_to_1tab(tab, sh, init);
	return (sh->arg[1]);
}

int	check_2_moove(t_sh *sh)
{
	int		i;

	i = 0;
	while (sh->arg[1][i])
	{
		if (sh->arg[1][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char *add_pwd(t_sh *sh, char *init)
{
	char	*tmp;
	char	*tmp2;
	char 	*tmp3;

	tmp = NULL;
	if ((sh->arg[1] != NULL && sh->arg[1][0] != '-') && check_2_moove(sh) != 0)
	{
		if (sh->arg[1][0] == '.' && sh->arg[1] != NULL)
		{
			if (ft_strlen(sh->PWD) > 1)
			{
				sh->PWD = cd_dot(sh, tmp);
				return (sh->PWD);
			}
			give_value_old_pwd(sh);
			return (sh->PWD);
		}
		sh->arg[1] = check_slash(sh, init);
	}
	if (sh->s_arg == 1 || sh->arg[1][0] == '#' || sh->arg[1][0] == '~' || sh->arg[1][0] == ';')
	{
		if (!(sh = go_home(sh)))
			return (NULL);
		return(sh->PWD);
	}
	else if (sh->arg[1][0] == '.' && sh->arg[1] != NULL)
	{
		if (ft_strlen(sh->PWD) > 1)
		{
			sh->PWD = cd_dot(sh, tmp);
			return (sh->PWD);
		}
		give_value_old_pwd(sh);
		return (sh->PWD);
	}
	else if (sh->arg[1][0] == '.' && sh->arg[1][1] == '\0')
		return (give_value_old_pwd(sh));
	else if (test_racine(sh) == 1)
	{
		ft_strdel(&sh->PWD);
		if (!(sh->PWD = ft_strdup("/")))
			return (NULL);
	}
	else if (sh->arg[1][0] == '-')
	{
		sh = go_old_pwd(sh);
		return(sh->PWD);
	}
	else
	{
		if (sh->arg[1][0] == '/' && sh->arg[1][1] != '\0')
		{
			ft_strdel(&sh->PWD);
			sh->PWD = ft_strdup(sh->arg[1]);
		}
		else
		{
			tmp2 = ft_strjoin(sh->PWD, "/");
			tmp3 = ft_strjoin(tmp2,  sh->arg[1]);
			ft_strdel(&sh->PWD);
			if (!(sh->PWD = ft_strdup(tmp3)))
				return (NULL);
			ft_strdel(&tmp2);
			ft_strdel(&tmp3);
		}
	}
	return (sh->PWD);
}

char **add_pwd_env(t_sh *sh)
{
	char	*tmp;
	char buf[126];

	if(!(tmp = 	ft_strjoin("PWD=", getcwd(buf, 126))))
	  return (NULL);
	sh->sh_env = modify_env(sh, "PWD", tmp);
	ft_strdel(&tmp);
	return(sh->sh_env);

}

t_sh *init_pwd(t_sh *sh)
{
	int i;
	char	*tmp;

	i = 0;
	while (i < sh->s_env)
	{
		if (ft_strncmp(sh->sh_env[i], "PWD=", 4) == 0)
		{
			if (!(tmp = ft_strsub(sh->sh_env[i], 4, (ft_strlen(sh->sh_env[i]) - 4))))
				return (NULL);
			ft_strdel(&sh->PWD);
			if (!(sh->PWD = ft_strdup(tmp)))
				return (NULL);
			ft_strdel(&tmp);
		}
		i++;
	}
	return(sh);
}
