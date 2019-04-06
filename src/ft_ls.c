/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 12:12:59 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 16:36:08 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		check_flag(char *av, int flag)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (!ft_strchr("lRart", av[i]))
		{
			ft_printf("ft_ls: illegal option -- %c\n", av[i]);
			ft_printf("usage: ft_ls [-lRart] [file ...]\n");
			return (0);
		}
		else
		{
			(av[i] == 'l') && (flag |= F_L);
			(av[i] == 'R') && (flag |= F_UR);
			(av[i] == 'a') && (flag |= F_A);
			(av[i] == 'r') && (flag |= F_LR);
			(av[i] == 't') && (flag |= F_T);
		}
		i++;
	}
	return (flag);
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

static void		print_path(t_ls *ls)
{
	while (ls && ls->path)
	{
		ft_printf("%s\n", ls->path);
		ls = ls->next;
	}
}

static t_ls		*allocate_ls(char **av, int ac, int i)
{
	t_ls			*ls;

	ls = NULL;
	(ac == 1) && add_list("", ".", &ls);
	while (ac >= 2 && av[i])
		add_list("", av[i++], &ls);
	return (ls);
}

int				main(int argc, char **argv)
{
	t_ls	*ls;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (argv[1] && argv[1][0] == '-')
		if (!(flag = check_flag(argv[1], 0)))
			return (-1);
	i = ((argv[1] && argv[1][0] == '-') && (argc > 1)) ? 2 : 1;
	(argc > 2) && sort_file(argv, argc, i);
	ls = allocate_ls(argv, argc, i);
	print_path(ls);
	print_ls(ls, flag, 1);
	free_ls(ls);
	return (0);
}
