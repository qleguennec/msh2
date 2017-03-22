/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:02:50 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/22 15:24:46 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libdict/libdict.h"
# include "liblst/liblst.h"
# include "libfmt/libfmt.h"

# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/dir.h>
# include <sys/stat.h>

// TODO remove debug includes
# include <stdio.h>
# include <assert.h>

int
	bi_env
	(t_dict *env
	, t_lst *inp
	, int *ret);
char
	*query_path
	(char *path
	, char *file);
char
	*query_path_env
	(t_dict *env
	, char *file);
int
	fork_exec
	(t_dict *env
	, char *path
	, t_lst *args);
int
	bi_exit
	(t_dict *env
	, t_lst *inp
	, int *ret);
int
	bi_cd
	(t_dict *env
	, t_lst *inp
	, int *ret);
int
	bi_setenv
	(t_dict *env
	, t_lst *inp
	, int *ret);
int
	bi_unsetenv
	(t_dict *env
	, t_lst *inp
	, int *ret);
int
	env_cpy_val
	(t_dict *env
	, char *key
	, t_vect *v);
void
	expand_input
	(t_dict *env
	, t_lst *inp);

#endif
