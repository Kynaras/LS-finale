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
    int j;

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
    if (argc == 1 || (argc - i == 1 && ft_strcmp(argv[i], "--") == 0))
    {
        dirs = ft_readdir(".", flags);
        ft_dellst(dirs);
	//	sleep (10);
        return (0);  
    }

    else if (argc >= 2)
    {
        j = 0;
        while (++j <= 2)
        {
            lst = j == 1 ? ft_arglst(argc, argv, i, 1) : ft_arglst(argc, argv, i, 2);
            ft_mergesort(&lst, flags);
            dirs = lst;
            if (lst != NULL)
            {
                while (lst)
                {
                    ft_readdir(lst->name, flags);
                    lst = lst->next;
                }
            }
            // else
            //     dirs = ft_readdir(".", flags);
            ft_dellst(dirs);
        }
    }
  // sleep(10); 
   return (0);
}
//}
