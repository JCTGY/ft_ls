/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 12:12:59 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/13 13:07:37 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		check_flag(char *av, int *flag)
{
	int		i;

	i = 0;
	while (av[i++])
	{
		if (!ft_strchr("1lRartdgSo", av[i]))
		{
			ft_printf("ft_ls: illegal option -- %c\n", av[i]);
			ft_printf("usage: ft_ls [1lRartdgSo] [file ...]\n");
			exit(1);
		}
		else
		{
			(av[i] == 'l') && (*flag |= F_L);
			(av[i] == 'R') && (*flag |= F_UR);
			(av[i] == 'a') && (*flag |= F_A);
			(av[i] == 'r') && (*flag |= F_LR);
			(av[i] == 't') && (*flag |= F_T);
			(av[i] == 'd') && (*flag |= F_DD);
			(av[i] == 'g') && (*flag |= F_G);
			(av[i] == 'S') && (*flag |= F_US);
			(av[i] == 'o') && (*flag |= F_O);
			(av[i] == '1') && (*flag |= F_ONE);
		}
	}
}

static int		sort_file(char **av, int ac, int i)
{
	int		j;
	char	*temp;

	temp = NULL;
	while (i < ac)
	{
		j = i + 1;
		while (j < ac)
		{
			if (ft_strcmp(av[i], av[j]) > 0)
			{
				temp = av[i];
				av[i] = av[j];
				av[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

static t_ls		*allocate_ls(char **av, int ac, int i)
{
	t_ls			*ls;

	ls = NULL;
	(ac == i) && add_list("", ".", &ls);
	while (ac >= 2 && av[i])
		add_list("", av[i++], &ls);
	return (ls);
}

int				main(int argc, char **argv)
{
	t_ls	*ls;
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		check_flag(argv[i], &flag);
		if (!flag)
		{
			ft_printf("ft_ls: -: No such file or directory\n");
			return (-1);
		}
		i++;
	}
	(argc > 2) && sort_file(argv, argc, i);
	ls = allocate_ls(argv, argc, i);
	(!(flag & F_DD)) ? open_ls(ls, flag, 1) : ls_dflag(ls);
	(flag & F_DD) ? print_ls(ls, flag) : 1;
	free_ls(&ls);
	return (0);
}
