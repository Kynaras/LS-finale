/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keverett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 09:15:38 by keverett          #+#    #+#             */
/*   Updated: 2019/07/31 09:15:42 by keverett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    ft_colours(n_list *lst, f_list flags)
{
    if (S_ISDIR(lst->sb.st_mode))
    {    
       if (S_IWOTH & lst->sb.st_mode && !(S_ISVTX & lst->sb.st_mode))
            ft_putstr("\033[30;43m");
       else
            ft_putstr("\033[34m"); 
    }
    else if (S_ISLNK(lst->sb.st_mode))
       ft_putstr("\033[35m"); 
    ft_putstr(lst->name);
    ft_putstr("\033[0m");
}
void    ft_regfiles(n_list *lst, f_list flags, s_list totals)
{
    if (*lst->name != '.')
        {
            if (flags.list == 1)
             {
                 ft_filestats(lst->sb, lst->path, totals);
                 ft_putchar(' ');
             }

             if (flags.colours  == 1)
                 ft_colours(lst, flags);
             else
                ft_putstr(lst->name);
            if (S_ISLNK(lst->sb.st_mode))
             {
                 ft_putstr(" -> ");
                 ft_linkname(lst->path);
             }
            ft_putchar('\n');
        }    
}

void    ft_hiddenfiles(n_list *lst, f_list flags, s_list totals)
{
    if (flags.list == 1)
    {
      ft_filestats(lst->sb, lst->path, totals);
      ft_putchar(' ');
    }
             ft_putstr(lst->name);
             if (S_ISLNK(lst->sb.st_mode))
             {
                 ft_putstr(" -> ");
                 ft_linkname(lst->path);
             }
             ft_putchar('\n');
}

void    ft_semihiddenfiles(n_list *lst, f_list flags, s_list totals)
{
    unsigned int check;
    
    check = 0;
    if (flags.list == 1 && ft_strcmp(lst->name, ".") != 0 && ft_strcmp(lst->name, "..") != 0)
    {
      check = 1;
      ft_filestats(lst->sb, lst->path, totals);
      ft_putchar(' ');
    }
    if (check == 1)
    {
             ft_putstr(lst->name);
             if (S_ISLNK(lst->sb.st_mode))
             {
                 ft_putstr(" -> ");
                 ft_linkname(lst->path);
             }
             ft_putchar('\n');
    }
}
void    ft_totalsize(n_list *lst)
{
    long long size;
	
    size = 0;
    while (lst)
    { 
        size += lst->sb.st_blocks;
        lst = lst->next;
    }
    ft_putstr("total ");
    ft_putlonglong(size);
    ft_putchar('\n');
}

void ft_printlst(n_list *lst, f_list flags)
{
    s_list totals;

    if (flags.list == 1 && lst != NULL)
    {
        ft_structstat(lst);
        totals = ft_totalsizelst(lst);
        ft_totalsize(lst);
    }
	while (lst != NULL)
    {   
        if (*lst->name == '.' && flags.hidden == 1) 
            ft_hiddenfiles(lst, flags, totals);
        else if (*lst->name == '.' && flags.semihidden == 1)
            ft_semihiddenfiles(lst, flags, totals);
        else
            ft_regfiles(lst, flags, totals);
        lst = lst->next;
    }
	return ;
}