/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:28:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/27 15:15:50 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENOPERM "minishell: cd: %s: Permission denied"

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
		VFMT(&path, "/%s", inp->data);
	}
	else
		VFMT(&path, "%s", inp->data);
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
	char		*path;
	t_dict_ent	*pwd;

	(void)ret;
	path = cd_get_path(env, inp);
	if (path == NULL)
		return (0);
	if (chdir(path) == -1)
	{
		ERR(ENOPERM, -1, path);
		free(path);
		return (-1);
	}
	pwd = dict_lookup(env, "PWD");
	if (pwd)
		dict_set(env, "OLDPWD", pwd->val.data, pwd->val.used);
	free(path);
	return (1);
}
