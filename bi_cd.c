/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:28:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/29 04:42:45 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENOPERM "minishell: cd: %s: permission denied"
#define ENOFILE "minishell: cd: %s: no such file or directory"

static char
	*cd_get_path
	(t_dict *env
	, t_lst *inp)
{
	t_vect	path;

	vect_init(&path);
	if (inp == NULL || *(char *)inp->data == '~')
		env_cpy_val(env, "HOME", &path);
	else if (*(char *)inp->data == '-')
		env_cpy_val(env, "OLDPWD", &path);
	else if (*(char *)inp->data != '/')
	{
		env_cpy_val(env, "PWD", &path);
		vfmt(0, &path, "/%s", inp->data);
	}
	else
		vfmt(0, &path, "%s", inp->data);
	if (path.data)
		vect_mset_end(&path, '\0', 1);
	return (path.data);
}

int
	bi_cd
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	char			*path;
	struct stat		st;
	t_dict_ent		*pwd;

	(void)ret;
	path = cd_get_path(env, inp);
	if (path == NULL)
		return (0);
	if (stat(path, &st) == -1)
	{
		err(-1, ENOFILE, path);
		free(path);
		return (-1);
	}
	if (chdir(path) == -1)
	{
		err(-1, ENOPERM, path);
		free(path);
		return (-1);
	}
	pwd = dict_lookup(env, "PWD");
	if (pwd)
		dict_set(env, "OLDPWD", pwd->val.data, pwd->val.used);
	free(path);
	return (1);
}
