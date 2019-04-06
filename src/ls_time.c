/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:16:37 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 16:17:14 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		help_t(t_ls *ls1, t_ls *ls2)
{
	if (ls1->stat.st_mtimespec.tv_sec >
				ls2->stat.st_mtimespec.tv_sec)
		return (1);
	else if (ls1->stat.st_mtimespec.tv_sec ==
				ls2->stat.st_mtimespec.tv_sec)
	{
		if (ls1->stat.st_mtimespec.tv_nsec >
				ls2->stat.st_mtimespec.tv_nsec)
			return (2);
	}
	return (0);
}

static t_ls		*sort_merge(t_ls *ls1, t_ls *ls2)
{
	t_ls	*p;
	t_ls	*ls;

	p = ft_memalloc(sizeof(t_ls));
	ls = p;
	free(p);
	while (ls1 && ls2)
	{
		if ((help_t(ls1, ls2)))
		{
			ls->next = ls1;
			ls = ls->next;
			ls1 = ls1->next;
		}
		else
		{
			ls->next = ls2;
			ls = ls->next;
			ls2 = ls2->next;
		}
	}
	ls->next = (ls1 != NULL) ? ls1 : ls2;
	return (p->next);
}

t_ls			*sort_time(t_ls *ls)
{
	t_ls	*ls1;
	t_ls	*ls2;

	if ((ls == NULL) || (ls->next == NULL))
		return (ls);
	ls1 = ls;
	ls2 = ls->next->next;
	while (ls2 && ls2->next)
	{
		ls1 = ls1->next;
		ls2 = ls2->next->next;
	}
	ls2 = ls1->next;
	ls1->next = NULL;
	return (sort_merge(sort_time(ls), sort_time(ls2)));
}
