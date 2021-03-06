/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_metainfo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/17 15:04:53 by rlutt             #+#    #+#             */
/*   Updated: 2017/09/09 13:27:37 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ls.h"

static void			ls_putpermtype(struct stat *st)
{
	if (S_ISREG(st->st_mode))
		ft_putchar('-');
	else if (S_ISDIR(st->st_mode))
		ft_putchar('d');
	else if (S_ISLNK(st->st_mode))
		ft_putchar('l');
	else if (S_ISBLK(st->st_mode))
		ft_putchar('b');
	else if (S_ISCHR(st->st_mode))
		ft_putchar('c');
	else if (S_ISSOCK(st->st_mode))
		ft_putchar('s');
	else if (S_ISFIFO(st->st_mode))
		ft_putchar('p');
	else
		ft_putchar('-');
}

void				ls_putperm(struct stat *st)
{
	ls_putpermtype(st);
	ft_putchar((st->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((st->st_mode & S_IWUSR) ? 'w' : '-');
	if (st->st_mode & S_ISUID)
		ft_putchar('S');
	else
		ft_putchar((st->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((st->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((st->st_mode & S_IWGRP) ? 'w' : '-');
	if (st->st_mode & S_ISGID)
		ft_putchar('S');
	else
		ft_putchar((st->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((st->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((st->st_mode & S_IWOTH) ? 'w' : '-');
	if (st->st_mode & S_ISVTX)
		ft_putchar('T');
	else
		ft_putchar((st->st_mode & S_IXOTH) ? 'x' : '-');
	ft_putchar(' ');
}

void				ls_getblksz(size_t *sz, t_lnode *tree, t_lsnfo *info)
{
	struct stat		st;
	char			*full;

	full = NULL;
	if (!tree)
		return ;
	if (tree->left)
		ls_getblksz(sz, tree->left, info);
	if (tree->right)
		ls_getblksz(sz, tree->right, info);
	if (!(full = ls_dirjoin(info->cdir, tree->name)))
		return ;
	if ((lstat(full, &st) != -1))
		*sz += st.st_blocks;
	ft_strdel(&full);
}

void				ls_putlink(char *path)
{
	char			buf[MXDIRLEN];

	ft_bzero(buf, MXDIRLEN);
	if (!(readlink(path, buf, MXDIRLEN)))
		return ;
	ft_putstr(" -> ");
	ft_putstr(buf);
}

void				ls_putmeta(t_lsnfo *info, char *name)
{
	t_meta		meta;

	if (!name)
		return ;
	ft_bzero(meta.time, MXNAMLEN);
	if (!(meta.fullpath = ls_dirjoin(info->cdir, name)))
		return ;
	if (lstat(meta.fullpath, &meta.st) != -1)
	{
		meta.date = ctime(&meta.st.st_mtime);
		ft_strcpy(meta.time, meta.date);
		meta.pw = getpwuid(meta.st.st_uid);
		meta.gp = getgrgid(meta.st.st_gid);
		ls_putperm(&meta.st);
		ft_printf("%3lld % 6s %7s % 6lld %.12s %s", meta.st.st_nlink,
		meta.pw->pw_name, meta.gp->gr_name, meta.st.st_size,
		&meta.time[4], name);
	}
	else
		ft_printf("ft_ls: %s: No such file or directory\n", meta.fullpath);
	if (S_ISLNK(meta.st.st_mode))
		ls_putlink(meta.fullpath);
	ft_putchar('\n');
	ft_strdel(&meta.fullpath);
}
