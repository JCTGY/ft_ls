/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 08:10:20 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/12 13:30:21 by jchiang-         ###   ########.fr       */
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

static void		print_name(t_ls *ls, int *r, int count, int flag)
{
	if (ls->name[0] != '.' && count > 1 && (!(flag & F_DD)))
	{
		if (*r == 1)
		{
			ft_printf("%s:\n", ls->path);
			*r = 2;
		}
		else
			ft_printf("\n%s:\n", ls->path);
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
		(!(flag & F_UR)) ? ft_strdel(&name) : 1;
		return (NULL);
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

int				open_ls(t_ls *ls, int flag, int r)
{
	t_ls	*f;
	int		count;

	if (!(flag & F_UR) && !r)
		return (0);
	count = 0;
	count_file(ls, &count);
	while (ls)
	{
		if (S_ISDIR(ls->stat.st_mode) &&
			(r || (ft_strcmp(ls->name, ".") && ft_strcmp(ls->name, ".."))))
		{
			print_name(ls, &r, count, flag);
			f = open_path(ls, flag);
			if (f != NULL)
			{
				sort_list(&f, flag);
				print_ls(f, flag);
				open_ls(f, flag, 0);
				free_ls(&f);
			}
		}
		ls = ls->next;
	}
	return (1);
}
