/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:33:44 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/12 13:28:48 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				free_ls(t_ls **ls)
{
	t_ls	*temp;

	if (!*ls)
		return (-1);
	while (*ls)
	{
		if (((*ls)->path) != NULL)
			ft_strdel(&((*ls)->path));
		if (((*ls)->name) != NULL)
			ft_strdel(&((*ls)->name));
		temp = (*ls)->next;
		ft_memdel((void **)&(*ls));
		*ls = temp;
	}
	return (0);
}

void			free_re(char **re)
{
	int		i;

	if (!re)
		return ;
	i = 0;
	while (re[i])
		ft_strdel(&(re[i++]));
	ft_memdel((void **)&re);
}

int				count_file(t_ls *ls, int *f_count)
{
	int		max_len;

	max_len = 0;
	while (ls)
	{
		max_len = MAX((int)ft_strlen(ls->name), max_len);
		*f_count = *f_count + 1;
		ls = ls->next;
	}
	return (max_len);
}

int				check_column(t_ls *ls, t_xy *xy)
{
	struct winsize		w;
	int					t_width;

	xy->maxlen = count_file(ls, &(xy->count));
	ioctl(0, TIOCGWINSZ, &w);
	t_width = w.ws_col;
	xy->col = (t_width >= xy->maxlen) ? (t_width / (xy->maxlen + 1)) : 1;
	xy->row = (xy->count % xy->col) ?
		(xy->count / xy->col + 1) : (xy->count / xy->col);
	return (0);
}

int				count_total(t_ls *ls, t_xy *xy)
{
	int		total;

	total = 0;
	while (ls)
	{
		total = ls->stat.st_blocks + total;
		ls = ls->next;
		xy->count = xy->count + 1;
	}
	return (total);
}
