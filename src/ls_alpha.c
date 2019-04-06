/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:19:04 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 16:28:16 by jchiang-         ###   ########.fr       */
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
		if (ft_strcmp(ls1->name, ls2->name) < 0)
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

t_ls			*sort_alpha(t_ls *ls)
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
	return (sort_merge(sort_alpha(ls), sort_alpha(ls2)));
}
