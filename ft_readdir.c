/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keverett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 10:32:41 by keverett          #+#    #+#             */
/*   Updated: 2019/07/31 10:32:43 by keverett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "time.h"

void		ft_recurse(t_v_list vars, t_f_list *flags)
{
	while (vars.dirs != NULL)
	{
		if (*vars.dirs->name != '.' || (flags->hidden == 1 && *vars.dirs->name
		== '.') || (flags->unsorted == 1 & *vars.dirs->name == '.'))
		{
			ft_putchar('\n');
			ft_putstr(vars.dirs->path);
			ft_putstr(":\n");
			vars.lst = ft_readdir(vars.dirs->path, flags);
			ft_dellst(vars.lst);
		}
		vars.dirs = vars.dirs->next;
	}
}

void		ft_readlsts(t_v_list *vars, char *path)
{
	char		*test;
	struct stat	sb;

	while ((vars->de = readdir(vars->dr)) != NULL)
	{
		test = NULL;
		ft_join(&test, path);
		ft_join(&test, "/");
		ft_join(&test, vars->de->d_name);
		if (vars->lst == NULL)
			vars->lst = ls_lstnew(vars->de->d_name, path);
		else if (vars->lst != NULL)
			ls_lstadd(vars->lst, ls_lstnew(vars->de->d_name, path));
		if (lstat(test, &sb) == 0 && S_ISDIR(sb.st_mode) &&
			ft_strcmp(vars->de->d_name, ".") != 0 &&
			ft_strcmp(vars->de->d_name, "..") != 0)
		{
			if (vars->dirs == NULL)
				vars->dirs = ls_lstnew(vars->de->d_name, path);
			else
				ls_lstadd(vars->dirs, ls_lstnew(vars->de->d_name, path));
		}
		free(test);
	}
}

void		ft_errcheck(t_v_list *vars, char *path, t_f_list *flags,
t_s_list *totals)
{
	if (errno == ENOTDIR)
	{
		if (flags->list == 1)
		{
			vars->lst = ls_lstnew(path, "/");
			free(vars->lst->path);
			vars->lst->path = ft_strdup(path);
			ft_structstat(vars->lst);
			*totals = ft_totalsizelst(vars->lst);
			ft_filestats(vars->lst->sb, vars->lst->path, *totals, flags);
			ft_putchar(' ');
		}
		ft_putstr(path);
		ft_putchar('\n');
	}
	else
	{
		ft_putstr("ft_ls: ");
		ft_putstr(ft_getname(path));
		ft_putstr(": ");
		perror("");
	}
}

void		ft_strucset(t_v_list *vars)
{
	vars->tmp = NULL;
	vars->dirs = NULL;
	vars->dr = NULL;
	vars->lst = NULL;
}

t_n_list	*ft_readdir(char *path, t_f_list *flags)
{
	t_v_list	vars;
	t_s_list	totals;

	ft_strucset(&vars);
	if (!(vars.dr = opendir(path)))
	{
		ft_errcheck(&vars, path, flags, &totals);
		return (vars.lst);
	}
	ft_readlsts(&vars, path);
	if (flags->unsorted == 0)
	{
		ft_mergesort(&vars.dirs, flags);
		ft_mergesort(&vars.lst, flags);
	}
	ft_printlst(vars.lst, flags);
	ft_dellst(vars.lst);
	closedir(vars.dr);
	if (flags->recursive == 1)
		ft_recurse(vars, flags);
	return (vars.dirs);
}
