/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lmeta.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 17:29:07 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/10 19:12:34 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ls.h"

void		ls_putpermtype(struct stat *st)
{
	if (st->st_mode == S_IFREG)
		ft_putchar('-');
	else if (st->st_mode == S_IFDIR)
		ft_putchar('d');
	else if (st->st_mode == S_IFLNK)
		ft_putchar('l');
	else if (st->st_mode == S_IFBLK)
		ft_putchar('b');
	else if (st->st_mode == S_IFCHR)
		ft_putchar('c');
	else if (st->st_mode == S_IFSOCK)
		ft_putchar('s');
	else if (st->st_mode == S_IFIFO)
		ft_putchar('p');
	else
		ft_putchar('-');

}

void		ls_putusr(struct stat *st)
{
	struct passwd *pw;

	pw = getpwuid(st->st_uid);
	ft_printf("%s\t" , pw->pw_name);
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
	ft_putchar('\t');
}

void		ls_putmeta(t_node *node, struct stat *st)
{
	ls_putpermtype(st);
	ls_putperm(st);
	ft_printf("%lld\t", st->st_nlink);
	ls_putusr(st);
	ft_printf("%s", ctime(&st->st_mtime));
	ft_printf("%s\t\n", node->name);
}
