/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keverett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 08:12:45 by keverett          #+#    #+#             */
/*   Updated: 2019/08/12 10:36:26 by keverett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int main(int argc, char **argv) 
{
    char error;
    n_list *lst;
    f_list flags;
    n_list *dirs;
    int i;

    lst = NULL;
    i = 0;
    ft_flagset(&flags);
    
    if (argc > 1)
        i = ft_readflag(argc, argv, &flags);

    if (i == -1)
    {
        error = ft_finderror(argc, argv);
        ft_putstr("ft_ls: illegal option -- ");
        ft_putchar (error);
        ft_putstr("\nusage: ft_ls [-Ralrt] [file ...]");
        return (0);
    }
    if (argc == 1)
    {
        dirs = ft_readdir(".", flags);
        ft_dellst(dirs);
	//	sleep (10);
        return (0);  
    }
    else if (argc >= 2)
    {
        lst = ft_arglst(argc, argv, i);
        ft_mergesort(&lst, flags);
    }

    dirs = lst;
    if (lst != NULL)
    {
        while (lst)
        {
            ft_readdir(lst->name, flags);
            lst = lst->next;
        }
    }
    else
    {
        dirs = ft_readdir(".", flags);
        //ft_dellst(dirs);
    }

    ft_dellst(dirs);

  // sleep(10); 
   return (0);
}
//}
