/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:09:30 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/13 14:22:27 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_print_name(t_ls *ls)
{
	char	link[NAME_MAX + 1];

	if (S_ISLNK(ls->stat.st_mode))
	{
		ft_bzero(link, NAME_MAX + 1);
		readlink(ls->path, link, NAME_MAX);
		ft_printf("%s -> %s\n", ls->name, link);
	}
	else
		ft_printf("%s\n", ls->name);
}

static char		**relocate_ls(t_ls *ls, t_xy xy)
{
	char	**re;
	int		i;

	re = NULL;
	if (!(re = (char **)ft_memalloc(sizeof(char *) * xy.count + 1)))
		return (0);
	i = 0;
	while (ls)
	{
		re[i] = ft_strdup(ls->name);
		i++;
		ls = ls->next;
	}
	re[i] = NULL;
	return (re);
}

static void		output_ls(t_ls *ls)
{
	t_xy	xy;
	int		x;
	int		y;
	char	**re;
	int		i;

	re = NULL;
	ft_bzero(&xy, sizeof(t_xy));
	check_column(ls, &xy);
	if (!(re = relocate_ls(ls, xy)))
		return ;
	x = -1;
	while (++x < xy.row)
	{
		y = -1;
		i = x;
		while (++y < xy.col && i < xy.count)
		{
			ft_printf("%-*s", xy.maxlen + 1, re[i]);
			i = i + xy.row;
		}
		ft_printf("\n");
	}
	if (re != NULL)
		free_re(re);
}

static void		output_detail_ls(t_ls *ls, int flag, t_in in)
{
	t_xy	xy;
	int		total;

	ft_bzero(&xy, sizeof(t_xy));
	total = count_total(ls, &xy);
	(!(flag & F_DD)) && ft_printf("total %d\n", total);
	while (ls)
	{
		ls_permission(ls);
		ft_printf("%*u", in.link, ls->stat.st_nlink);
		(!(flag & F_G)) &&
			ft_printf(" %-*s ", in.usr, getpwuid(ls->stat.st_uid)->pw_name);
		(!(flag & F_O)) &&
			ft_printf(" %-*s ", in.grp, getgrgid(ls->stat.st_gid)->gr_name);
		(flag & F_G && flag & F_O) && ft_putnchar(2, ' ');
		ls_size(ls, in);
		ls_time(ls);
		ls_print_name(ls);
		ls = ls->next;
	}
}

void			print_ls(t_ls *ls, int flag)
{
	t_in	in;

	if ((flag & F_L) || (flag & F_O) || (flag & F_G))
	{
		ft_bzero(&in, sizeof(t_in));
		ls_index(ls, &in);
		output_detail_ls(ls, flag, in);
	}
	else if (flag & F_ONE)
	{
		while (ls)
		{
			ft_printf("%s\n", ls->name);
			ls = ls->next;
		}
	}
	else
		output_ls(ls);
}
