/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lout.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:25:51 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/13 13:08:04 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_size(t_ls *ls, t_in in)
{
	if (S_ISCHR(ls->stat.st_mode) || S_ISBLK(ls->stat.st_mode))
	{
		ft_printf(" %*d", in.ma, major(ls->stat.st_rdev));
		ft_printf(", %*d ", in.mi, minor(ls->stat.st_rdev));
	}
	else
		ft_printf(" %*lld ", in.sz, ls->stat.st_size);
}

void		ls_time(t_ls *ls)
{
	char	**s;
	time_t	t;
	int		i;

	time(&t);
	s = ft_strsplit(ctime(&(ls->stat.st_mtimespec.tv_sec)), ' ');
	ft_printf("%s %2s", s[1], s[2]);
	if ((ft_strstr(ctime(&t), s[4])))
		ft_printf(" %.5s ", s[3]);
	else
		ft_printf(" %5.4s ", s[4]);
	i = 0;
	while (s[i])
		ft_strdel(&s[i++]);
	free(s);
}

void		ls_index(t_ls *ls, t_in *in)
{
	while (ls)
	{
		in->link = MAX(ft_count_digit(ls->stat.st_nlink, 10), in->link);
		in->usr =
			MAX((int)ft_strlen(getpwuid(ls->stat.st_uid)->pw_name), in->usr);
		in->grp =
			MAX((int)ft_strlen(getgrgid(ls->stat.st_gid)->gr_name), in->grp);
		in->sz = MAX(ft_count_digit(ls->stat.st_size, 10), in->sz);
		if (S_ISCHR(ls->stat.st_mode) || S_ISBLK(ls->stat.st_mode))
		{
			in->ma = MAX(ft_count_digit(major(ls->stat.st_rdev), 10), in->ma);
			in->mi = MAX(ft_count_digit(minor(ls->stat.st_rdev), 10), in->mi);
			in->sz = MAX(in->ma + in->mi + 2, in->sz);
		}
		ls = ls->next;
	}
}

void		ls_permission(t_ls *ls)
{
	char	chmod[12];
	int		mode;

	mode = ls->stat.st_mode;
	chmod[0] = ls_file_type(mode);
	chmod[1] = (S_IRUSR & mode) ? 'r' : '-';
	chmod[2] = (S_IWUSR & mode) ? 'w' : '-';
	chmod[3] = (S_IXUSR & mode) ? 'x' : '-';
	chmod[4] = (S_IRGRP & mode) ? 'r' : '-';
	chmod[5] = (S_IWGRP & mode) ? 'w' : '-';
	chmod[6] = (S_IXGRP & mode) ? 'x' : '-';
	chmod[7] = (S_IROTH & mode) ? 'r' : '-';
	chmod[8] = (S_IWOTH & mode) ? 'w' : '-';
	chmod[9] = (S_IXOTH & mode) ? 'x' : '-';
	chmod[10] = ls_get_acl(ls->path);
	chmod[11] = '\0';
	if (S_ISUID & mode)
		chmod[3] = (chmod[3] == '-') ? 'S' : 's';
	if (S_ISGID & mode)
		chmod[6] = (chmod[6] == '-') ? 'S' : 's';
	if (S_ISVTX & mode)
		chmod[9] = (chmod[9] == '-') ? 'T' : 't';
	ft_printf("%s ", chmod);
}
