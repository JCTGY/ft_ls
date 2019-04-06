/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 08:10:20 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 16:37:40 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*only_name(char *name)
{
	int		i;
	int		len;
	char	*new_name;

	len = 0;
	i = 0;
	while (name[len])
		len++;
	new_name = ft_strnew(len);
	while (len > 0 && name[len] != '/')
		len--;
	len++;
	while (name[len] && name[len] != '/')
		new_name[i++] = name[len++];
	return (new_name);
}

static void		print_path(t_ls *ls)
{
	while (ls && ls->path)
	{
		ft_printf("%s\n", ls->path);
		ls = ls->next;
	}
}

static t_ls		*open_path(t_ls *ls, int flag)
{
	t_ls			*begin;
	DIR				*file;
	struct dirent	*f;
	char			*name;

	begin = NULL;
	if (!(file = opendir(ls->path)))
	{
		name = (ft_strchr(ls->name, '/')) ? only_name(ls->name) : ls->name;
		ft_printf("ft_ls: %s: %s\n", name, strerror(errno));
		ft_strdel(&name);
		return (0);
	}
	while ((f = readdir(file)))
	{
		if (f->d_name[0] != '.' || (flag & F_A))
			add_list(ls->path, f->d_name, &begin);
	}
	if (file)
		closedir(file);
	return (begin);
}

int				print_ls(t_ls *ls, int flag, int r)
{
	t_ls	*f;

	if (!(flag & F_UR) && !r)
		return (0);
	while (ls)
	{
		if (S_ISDIR(ls->stat.st_mode))
		{
			f = open_path(ls, flag);
			if (f)
			{
				sort_list(&f, flag);
				print_path(f);
				print_ls(f, flag, 0);
				free_ls(f);
			}
		}
		ls = ls->next;
	}
	return (1);
}
