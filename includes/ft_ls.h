/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchiang- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 13:42:54 by jchiang-          #+#    #+#             */
/*   Updated: 2019/04/13 14:10:51 by jchiang-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** bouns ACL, column, -d -g -S -o flag
** sys/stat for aceese stat of the file
** sys/type using the type
** dirent using DIR
** limit using pathmax
** errno using sterror
** TIOCSWINSZ generatre terminal info
** STDIN_FILENO file input
** termios using terminal info
** sys/ioctl using ioctl
** pwd.h getpwuid
** grp.h getgrgid
** time.h to get the time by ctime
*/
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

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
# define F_DD		(1 << 5)
# define F_G		(1 << 6)
# define F_US		(1 << 7)
# define F_O		(1 << 8)
# define F_ONE		(1 << 9)

typedef struct		s_in
{
	int				link;
	int				usr;
	int				grp;
	int				sz;
	int				ma;
	int				mi;
}					t_in;

typedef struct		s_xy
{
	int				col;
	int				row;
	int				maxlen;
	int				count;
}					t_xy;

typedef struct		s_ls
{
	char			*path;
	char			*name;
	struct stat		stat;
	struct s_ls		*next;
}					t_ls;

int					add_list(char *path, char *name, t_ls **ls);
int					open_ls(t_ls *ls, int flag, int r);
int					free_ls(t_ls **ls);
int					sort_list(t_ls **begin, int flag);
int					count_file(t_ls *ls, int *f_count);
int					count_total(t_ls *ls, t_xy *xy);
int					check_column(t_ls *ls, t_xy *xy);
int					ls_dflag(t_ls *ls);
t_ls				*sort_time(t_ls *ls);
t_ls				*sort_alpha(t_ls *ls);
t_ls				*sort_size(t_ls *ls);
void				print_ls(t_ls *ls, int flag);
void				free_re(char **re);
void				ls_index(t_ls *ls, t_in *in);
void				ls_permission(t_ls *ls);
void				ls_time(t_ls *ls);
void				ls_size(t_ls *ls, t_in in);
char				ls_file_type(int mode);
char				ls_get_acl(char *path);

#endif
