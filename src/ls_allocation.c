/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_allocation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:16:28 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/09 19:49:12 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				check_path(char *path, struct stat *buffer)
{
	if ((lstat(path, buffer)) == -1)
	{
		ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (1);
}

static void		store_path(char *p, char *path, char *name)
{
	int		i;

	i = 0;
	while (*path)
		p[i++] = *path++;
	if (i)
		p[i++] = '/';
	while (*name)
		p[i++] = *name++;
	p[i] = '\0';
}

static t_ls		*store_list(char *path, char *name, struct stat buffer)
{
	int		i;
	t_ls	*ls;

	i = 0;
	if (!(ls = (t_ls *)ft_memalloc(sizeof(t_ls))))
		return (0);
	if (!(ls->path = ft_strnew((int)ft_strlen(path))))
		return (0);
	while (*path)
	{
		ls->path[i] = *path;
		i++;
		path++;
	}
	ls->path[i] = '\0';
	ls->stat = buffer;
	ls->name = ft_strdup(name);
	ls->next = NULL;
	return (ls);
}

int				add_list(char *path, char *name, t_ls **ls)
{
	struct stat		buffer;
	char			p[PATH_MAX];

	store_path(p, path, name);
	if (!*ls && check_path(p, &buffer))
		*ls = store_list(p, name, buffer);
	else if (*ls && check_path(p, &buffer))
	{
		while ((*ls)->next)
			ls = &(*ls)->next;
		(*ls)->next = store_list(p, name, buffer);
	}
	return (0);
}
