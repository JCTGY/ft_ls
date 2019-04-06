/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:33:44 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 16:38:23 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				free_ls(t_ls *ls)
{
	t_ls	*temp;

	if (!ls)
		return (-1);
	while (ls)
	{
		if (ls->path)
			ft_strdel(&ls->path);
		if (ls->name)
			ft_strdel(&ls->name);
		temp = ls->next;
		ft_memdel((void **)&ls);
		ls = temp;
	}
	return (0);
}
