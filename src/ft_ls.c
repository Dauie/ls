/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 09:46:56 by rlutt             #+#    #+#             */
/*   Updated: 2017/04/18 12:36:20 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_ls.h"

void 			manage_lsattrib(t_lsnfo *db)
{
	if (db->a_flg == TRUE && db->A_flg == TRUE)
		db->A_flg = FALSE;
}

int 		ls_vrfydir(t_lsnfo *db, char *argstr)
{
	DIR		*chkdir;
	char	**tmp;

	if (!(chkdir = opendir(argstr)))
	{
		ft_printf("ft_ls: %s: No such file or directory\n", argstr);
		return (0);
	}
	closedir(chkdir);
	tmp = db->dirs;
	if (!(db->dirs = ft_tbladdl(db->dirs, argstr)))
	 	return (ft_puterror(-3));
	db->dirc++;
	ft_printf("%d\n", db->dirc);
	ft_puttbl(db->dirs);
	if (tmp)
		ft_tbldel(tmp);
	return (1);
}

int 		ls_anaargs(t_lsnfo *db)
{
	int		i;

	i = -1;
	while (db->args[++i])
	{
		if (*db->args[i] == '-')
		{
			if (!(ls_tickargs(db, db->args[i])))
				return (0);
		}
		else
		{
			if (!(ls_vrfydir(db, db->args[i])))
				return (0);
		}
	}
	ft_tbldel(db->args);
	return (1);
}

int 			ls_chkdirnam(t_lsnfo *db, char *dirnam)
{
	if (db->a_flg == TRUE)
		return (0);
	if (db->a_flg == FALSE && db->A_flg == FALSE && dirnam[0] == '.')
		return (1);
	if (db->A_flg == TRUE && (ft_strcmp(".", dirnam) == 0))
		return (1);
	if (db->A_flg == TRUE && (ft_strcmp("..", dirnam) == 0))
		return (1);
	return (0);
}

int				ls_reg(t_lsnfo *db)
{
	t_node		*tree;
	struct dirent	*sd;
	DIR			*ddir;

	if (!(ddir = opendir(".")))
		return (ft_puterror(-4));
	tree = NULL;
	while ((sd = readdir(ddir)) != NULL)
	{
		if (ls_chkdirnam(db, sd->d_name))
			continue ;
		if (db->t_flg == TRUE)
			ls_addtnodet(&tree, sd->d_name, sd->d_type, db);
		else
			ls_addtnoden(&tree, sd->d_name, sd->d_type, db);
	}
	if (db->r_flg == TRUE)
		ls_revprinttree(tree);
	else
		ls_printtree(tree);
	closedir(ddir);
	return (0);
}

int			ls_start(t_lsnfo *db)
{
	manage_lsattrib(db);
	if (db->dirc == 0)
		ls_reg(db);
	return (1);
}

int				main(int ac, char **av)
{
	t_lsnfo			db;

	ls_initdb(&db);
	if (ac > 1)
	{
		db.args = ft_tbldup(&av[1], (ac - 1));
		if (!(ls_anaargs(&db)))
			return (1);
	}
	ls_start(&db);
	return (0);
}