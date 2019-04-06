/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 13:42:54 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/06 16:24:49 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <limits.h>
# include <string.h>
# include <errno.h>

# define MAX(a,b) ((a > b) ? a : b)
# define MIN(a,b) ((a < b) ? a : b)

/*
** define the flags -l, -R, -a, -r, and -t
*/
# define F_L		(1 << 0)
# define F_UR		(1 << 1)
# define F_A		(1 << 2)
# define F_LR		(1 << 3)
# define F_T		(1 << 4)

typedef struct		s_ls
{
	char			*path;
	char			*name;
	struct stat		stat;
	struct s_ls		*next;
}					t_ls;

int					add_list(char *path, char *name, t_ls **ls);
int					print_ls(t_ls *ls, int flag, int r);
int					free_ls(t_ls *ls);
int					sort_list(t_ls **begin, int flag);
t_ls				*sort_time(t_ls *ls);
t_ls				*sort_alpha(t_ls *ls);

#endif
