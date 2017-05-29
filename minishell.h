/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 13:02:50 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/29 04:48:00 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libdict/libdict.h"
# include "liblst/liblst.h"
# include "libfmt/libfmt.h"

# include <errno.h>
# include <signal.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char	*query_path(char *path, char *file);
char	*query_path_env(t_dict *env, char *file);
int		bi_cd(t_dict *env, t_lst *inp, int *ret);
int		bi_echo(t_dict *env, t_lst *inp, int *ret);
int		bi_env(t_dict *env, t_lst *inp, int *ret);
int		bi_exit(t_dict *env, t_lst *inp, int *ret);
int		bi_setenv(t_dict *env, t_lst *inp, int *ret);
int		bi_unsetenv(t_dict *env, t_lst *inp, int *ret);
int		env_cpy_val(t_dict *e, char *k, t_vect *v);
int		fork_exec(t_dict *env, char *path, t_lst *args);
int		inp_query(t_dict *env, t_lst *inp);
void	expand_input(t_dict *env, t_lst *inp);
void	sig_int(int sig);
void	malloc_err(void *arg);

#endif
