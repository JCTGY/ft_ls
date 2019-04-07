/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:16:28 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 17:00:26 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_ls		*sort_reverse(t_ls *ls)
{
	t_ls	*next;
	t_ls	*current;
	t_ls	*prev;

	current = ls;
	next = NULL;
	prev = NULL;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

int				sort_list(t_ls **begin, int flag)
{
	*begin = (!(flag & F_T)) ? sort_alpha(*begin) : *begin;
	*begin = (flag & F_T) ? sort_time(*begin) : *begin;
	*begin = (flag & F_LR) ? sort_reverse(*begin) : *begin;
	return (0);
}
