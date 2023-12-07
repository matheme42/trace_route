/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxence <maxence@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:05:20 by matheme           #+#    #+#             */
/*   Updated: 2022/03/13 21:32:32 by maxence          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int     ft_check_complexe_option(char c, int value)
{
    int ret;

    ret = 1;
    ret = (c == 'm' && (value <= 0 || value > 255)) ? 0 : ret;
    ret = (c == 'f' && (value <= 0 || value > 255)) ? 0 : ret;
    ret = (c == 'q' && (value <= 0 || value > 10)) ? 0 : ret;
    ret = (c == 'w' && (value <= 0 || value > 60)) ? 0 : ret;
    return (ret);
}

/*
** liste des options
** pour rajouter une option il suffit de recopier le patern suivant
*/

static int	ft_complexe_option(char *str, option option)
{
    int i;

    option[*str] = ft_atoi(&str[1]);
    if (!ft_check_complexe_option(*str, option[*str]))
        usage(*str);
    i = 1;
    while ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-')
        i++;
	return (i);
}

/*
** permet de scruter les options
** aussi bien sur le meme arg que sur plusieur arg
*/

static void ft_option(int ac, char **av, option opt)
{
	int	i;

	i = 1;
	if ((*av)[0] != '-' || !(*av)[1])
		return ;
	while ((*av)[i])
	{
        ft_strchr(LIST_OPTION, (*av)[i]) == NULL ? usage((*av)[i]) : 0;
        if (ft_strchr(LIST_COMPLEXE_OPTION, (*av)[i]) == NULL)
        {
            opt[(int)(*av)[i]] = 1;
            i++;
        }
        else
        {
		    i += ft_complexe_option(&(*av)[i], opt);
        }
	}
	if (ac > 1)
		ft_option(ac - 1, &av[1], opt);
}

/*
** permet de ce diriger apres les options
** la fonction prend en compte le cas ou il n'y a que le tiret
** et aucune option
** dans ce cas la fonction ne deplace pas le pointeur
*/

static char	**ft_go_after_option(char **av)
{
	if (*av && **av == '-' && (*av)[1])
		return (ft_go_after_option(&av[1]));
	return (av);
}

/*
** fonction visible de l'exterieur
** elle permet de recuperer les options via ...
** ...l'adresse d'un int que l'on passe en parametre
** et elle retourne l'argument qui suit les options
*/

char		**get_option(int ac, char **av, option opt)
{
	ft_option(ac, av, opt);
	return (ft_go_after_option(av));
}
