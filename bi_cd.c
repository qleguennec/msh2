/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:28:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/22 11:10:31 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	cd_get_ent
	(t_dict *env
	, t_vect *path
	, char *key)
{
	t_dict_ent	*ent;

	ent = dict_lookup(env, key);
	if (ent == NULL)
		return (ERR("minishell: cd: %s not set", 0, key));
	assert(ent->val.used >= 1);
	vect_add(path, ent->val.data, ent->val.used - 1);
	return (1);
}

static char
	*cd_get_path
	(t_dict *env
	, t_lst *inp)
{
	t_vect	path;

	vect_init(&path);
	if (inp == NULL || *(char *)inp->data == '~')
	{
		cd_get_ent(env, &path, "HOME");
		if (inp != NULL)
			VFMT(&path, "%s", inp->data + 1);
	}
	else if (*(char *)inp->data == '-')
		cd_get_ent(env, &path, "OLDPWD");
	else if (*(char *)inp->data != '/')
	{
		cd_get_ent(env, &path, "PWD");
		VFMT(&path, "/%s", inp->data);
	}
	else
		VFMT(&path, "%s", inp->data);
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
	pwd = dict_lookup(env, "PWD");
	if (chdir(path) == -1)
	{
		ERR("minishell: cd: %s: Permission denied", -1, path);
		free(path);
		return (-1);
	}
	if (pwd)
		dict_set(env, "OLDPWD", pwd->val.data, pwd->val.used);
	free(path);
	return (1);
}
