/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttresori <ttresori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:32:15 by carmand           #+#    #+#             */
/*   Updated: 2017/10/19 02:20:03 by ttresori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_minishell.h"

void	put_env(char **sh_env, int s_env)
{
	int	i;

	i = 0;
	while (i < s_env)
	{
		ft_putendl(sh_env[i]);
		i++;
	}
}

int		search_env(t_sh *sh, char *line)
{
	int i;

	i = 0;
	while(i < sh->s_env)
	{
		if (ft_strncmp(sh->sh_env[i], line, ft_strlen(line)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		ft_strlen_2d(t_sh *sh)
{
	int i;

	i = 0;
	while(i < sh->s_env)
		i++;
	return(i);
}

char	**ft_cpy_2char(t_sh *sh, char **init)
{
	int i;

	i = 0;
	if (!(sh->sh_env = (char**)malloc(sizeof(char*) * sh->s_env)))
		return (init);
	while (i < sh->s_env)
	{
		sh->sh_env[i] = ft_strdup(init[i]);
		i++;
	}
	free_tab(init, sh->s_env);
	return (sh->sh_env);
}

char	**realloc_env(t_sh *sh, char *place)
{
	char	**new;
	char	*tmp;
	int 	start;

	start = 0;
	if (!(new = (char**)malloc(sizeof(char*) * (sh->s_env + 1))))
		return (NULL);
	tmp = ft_strdup(place);
	while(start < sh->s_env)
	{
		new[start] = ft_strdup(sh->sh_env[start]);
		start++;
	}
	new[start] = ft_strdup(tmp);
	ft_strdel(&tmp);
	if (start > 0)
		free_tab(sh->sh_env, sh->s_env);
	sh->s_env = sh->s_env + 1;
	sh->sh_env = ft_cpy_2char(sh, new);
	return (sh->sh_env);
}

char	 **modify_env(t_sh *sh, char *line, char *modify)
{
	int 	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (line == NULL)
	{
		sh->sh_env = add_env(sh, i);
		return (sh->sh_env);
	}
	if (!(tmp2 = ft_strjoin(line, "=")))
		return (NULL);
	if (!(tmp = ft_strjoin(tmp2, modify)))
		return (NULL);
	if ((i = search_env(sh, line)) != -1)
	{

		ft_strdel(&sh->sh_env[i]);
		sh->sh_env[i] = ft_strdup(tmp);
	}
	else
		if (!(sh->sh_env = realloc_env(sh, modify)))
			return (NULL);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	return (sh->sh_env);
}

char	**add_env(t_sh *sh , int i)
{
	int		j;
	int		s;
	char	**new;
	char	*tmp;
	char	*tmp2;

	j = 0;
	s = 0;
	if (i == -1)
	{
		new = NULL;
		while (sh->sh_env[j] != NULL)
			j++;
		if (!(new = (char**)malloc(sizeof(char*) * (j + 2))))
		   return (NULL);
		while (s < j)
		{
			if (!(new[s] = ft_strdup(sh->sh_env[s])))
				return (NULL);
			s++;
		}
		if (!(tmp = ft_strjoin(sh->arg[1], "=")))
			return (NULL);
		if (!(tmp2 = ft_strjoin(tmp, sh->arg[2])))
			return (NULL);
		if (!(new[s] = ft_strdup(tmp2)))
			return (NULL);
		new[s + 1] = NULL;
		sh->sh_env = NULL;
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		return (new);
	}
	else
	{
		new = NULL;
		sh->sh_env[i] = NULL;
		if (!(tmp = ft_strjoin(sh->arg[1], "=")))
			return (NULL);
		if (!(tmp2 = ft_strjoin(tmp, sh->arg[2])))
			return (NULL);
		if (!(sh->sh_env[i] = ft_strdup(tmp2)))
			return (NULL);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (sh->sh_env);
}

char	**set_env(t_sh *sh)
{
	int 	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	if (!(tmp = ft_strjoin(sh->arg[1], "=")))
		return (NULL);
	if (search_env(sh, tmp) > 0)
	{
		ft_strdel(&tmp);
		return(sh->sh_env);
	}
	else if (!(tmp2 = ft_strjoin(tmp, sh->arg[2])))
	{
		ft_strdel(&tmp);
		return (sh->sh_env);
	}
	ft_strdel(&tmp);
//	sh->sh_env = add_env(sh, i);
	sh->sh_env = modify_env(sh, NULL, tmp2);
	ft_strdel(&tmp2);
	return(sh->sh_env);
}

char	**unset_env(t_sh *sh)
{
	int		i;
	int 	j;
	int		k;
	char	**new;

	i = 0;
	j = -1;
	new = NULL;
	k = 0;
	if (sh->s_arg == 1)
		return (sh->sh_env);
	j = search_env(sh, sh->arg[1]);
	if (j == -1)
		return (sh->sh_env);
	else
	{
		if (!(new = (char**)malloc(sizeof(char*) * (sh->s_env))))
			return (NULL);
		while (k != j)
		{
			if (!(new[k] = ft_strdup(sh->sh_env[k])))
				return (NULL);
			k++;
		}
		while (k != (sh->s_env - 1))
		{
			if (!(new[k] = ft_strdup(sh->sh_env[k + 1])))
				return (NULL);
			k++;
		}
	}
//	new[k + 1] = NULL;
	free_tab(sh->sh_env, sh->s_env);
	sh->s_env--;
	return (new);
}
