/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlutt <rlutt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 11:11:10 by rlutt             #+#    #+#             */
/*   Updated: 2017/05/15 14:49:47 by rlutt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ft_ls_H
# define ft_ls_H

#include "../libft/incl/bool.h"
#include "../libft/incl/char.h"
#include "../libft/incl/cnvrsn.h"
#include "../libft/incl/gnl.h"
#include "../libft/incl/lst.h"
#include "../libft/incl/mem.h"
#include "../libft/incl/num.h"
#include "../libft/incl/put.h"
#include "../libft/incl/printf.h"
#include <dirent.h>
#include <time.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

# define MXDIRLEN 1024
# define MXNAMLEN 256
# define MXTYPLEN 42

typedef struct		s_cduo
{
	char *uno;
	char *dos;
}					t_cduo;

typedef struct		s_rnode
{
	char			name[MXNAMLEN];
	struct s_rnode	*left;
	struct s_rnode	*right;
}					t_rnode;

typedef struct		s_trirnode
{
	t_rnode			*elem;
	t_rnode			*ntmp;
	t_rnode			*ttmp;
}					t_trirnode;

typedef struct		s_node
{
	char			cdir[MXNAMLEN];
	char 			name[MXNAMLEN];
	struct stat		stat;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct		s_trinode
{
	t_node			*elem;
	t_node			*ntmp;
	t_node			*ttmp;
}					t_trinode;

typedef struct		s_lsnfo
{
	char			**args;
	t_rnode			*dirs;
	size_t			dirc;
	char			type[MXTYPLEN];
	char			cdir[MXNAMLEN];
	t_blean			l_flg;
	t_blean			A_flg;
	t_blean			a_flg;
	t_blean			R_flg;
	t_blean			r_flg;
	t_blean			t_flg;
}					t_lsnfo;

int					main(int ac, char **av);
int					list_dir(t_lsnfo *db, char *dir);
int					ls_start(t_lsnfo *db);
void				ls_addtnoden(t_node **tree, char *name);
void				ls_addtnodet(t_node **tree, char *name);
void				ls_addrnoden(t_rnode **tree, char *name);
void				ls_clrtree(t_node **tree);
void				ls_clrrtree(t_rnode **tree);
char				*ls_dirjoin(const char *s1, const  char *s2);
void				ls_initdb(t_lsnfo *db);
void				ls_freedb(t_lsnfo *db);
void				ls_initnode(t_node *node);
void				ls_initrnode(t_rnode *node);
void				ls_getblksz(size_t *sz, t_node *tree, t_lsnfo *info);
void				ls_putmeta(t_node *node, t_lsnfo *info);
void				ls_manageput(t_node *tree, t_lsnfo *db);
t_rnode				*ls_getdirlist(char *dir, t_lsnfo *db);
int					ls_recurse(t_lsnfo *db, t_rnode *dirs);
int					ls_preprecurs(t_lsnfo *db);
int					ls_treesearch(t_node *tree, char *name);
unsigned int		ls_diramnt(t_node *tree);
void				ls_dirtree(t_node *tree, t_lsnfo *db, char **av, size_t inx);
int					ls_chkdirnam(t_lsnfo *db, char *dirnam);
int					ls_anaargs(t_lsnfo *db);
# endif
