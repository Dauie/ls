/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lmeta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 17:29:07 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/11 16:19:52 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ls.h"

void		ls_putpermtype(struct stat *st)
{
	if (st->st_mode & S_IFREG)
		ft_putchar('-');
	else if (st->st_mode & S_IFDIR)
		ft_putchar('d');
	else if (st->st_mode & S_IFLNK)
		ft_putchar('l');
	else if (st->st_mode & S_IFBLK)
		ft_putchar('b');
	else if (st->st_mode & S_IFCHR)
		ft_putchar('c');
	else if (st->st_mode & S_IFSOCK)
		ft_putchar('s');
	else if (st->st_mode & S_IFIFO)
		ft_putchar('p');
}

void		ls_putperm(struct stat *st)
{
	ls_putpermtype(st);
	ft_putchar((st->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((st->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((st->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((st->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((st->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((st->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((st->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((st->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((st->st_mode & S_IXOTH) ? 'r' : '-');
	ft_putchar(' ');
}

//get the size going, then a blksize static var may work.
void				ls_putmeta(t_node *node, t_lsnfo *info)
{
	struct stat		st;
	struct passwd	*pw;
	struct group	*gp;
	char			*tmp;
	char			time[MXNAMLEN];
	
	lstat(ls_dirjoin(info->cdir, node->name), &st);
	ft_bzero(time, MXNAMLEN);
	tmp = ctime(&st.st_mtime);
	ft_strcpy(time, &tmp[4]);
	ft_strdel(&tmp);
	ls_putperm(&st);
	pw = getpwuid(st.st_uid);
	gp = getgrgid(st.st_gid);
	ft_printf("%3lld % 6s %9s % 6lld  %.12s  %s\n", st.st_nlink, pw->pw_name,
			gp->gr_name, st.st_size , time, node->name);
}
