/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lhep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:14:10 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/13 12:26:05 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ls_dflag(t_ls *ls)
{
	while (ls)
	{
		ft_strdel(&ls->name);
		ls->name = ft_strdup(ls->path);
		ls = ls->next;
	}
	return (0);
}

/*
** XATTR_NOFOLLOW do not follow symbolic links.
** listxattr() normally lists attributes of the target of path if
** it is a symbolic link. With this option, listxattr() will list
** attributes of the link itself.
*/

char		ls_get_acl(char *path)
{
	acl_t	acl;

	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		return ('+');
	}
	return (' ');
}

/*
** S_ISREG(m)  is it a regular file
** S_ISDIR(m)  directory
** S_ISCHR(m)  character device
** S_ISBLK(m)  block device
** S_ISFIFO(m) FIFO (named pipe)
** S_ISLNK(m)  symbolic link
** S_ISSOCK(m) socket
*/

char		ls_file_type(int mode)
{
	if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}
