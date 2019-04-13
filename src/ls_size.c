/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:23:09 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/12 18:34:35 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_ls		*sort_merge(t_ls *ls1, t_ls *ls2)
{
	t_ls	*p;
	t_ls	*ls;

	p = ft_memalloc(sizeof(t_ls));
	ls = p;
	free(p);
	while (ls1 && ls2)
	{
		if (ls1->stat.st_size >= ls2->stat.st_size)
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

t_ls			*sort_size(t_ls *ls)
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
	return (sort_merge(sort_size(ls), sort_size(ls2)));
}
