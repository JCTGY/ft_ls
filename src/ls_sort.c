/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 13:16:28 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 16:27:09 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				sort_list(t_ls **begin, int flag)
{
	*begin = (!(flag & F_T)) ? sort_alpha(*begin) : *begin;
	*begin = (flag & F_T) ? sort_time(*begin) : *begin;
//	(flag & F_LR) && sort_reverse(ls);
	return (0);
}
