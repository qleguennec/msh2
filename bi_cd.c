/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:28:44 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/17 15:05:00 by qle-guen         ###   ########.fr       */
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
	assert(ent == NULL || ent->val.used != 0);
	if (ent == NULL || ent->val.used < 2)
		return (0);
	vect_add(path, ent->val.data, ent->val.used);
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
		if (cd_get_ent(env, &path, "HOME") == 0)
		{
			ERR("minishell: cd: no home directory (HOME not set)", 0, 0);
			return (NULL);
		}
		if (inp != NULL)
			vect_add(&path, inp->data + 1, ft_strlen(inp->data + 1));
	}
	else if (*(char *)inp->data != '/' && cd_get_ent(env, &path, "PWD"))
	{
		vect_mset_end(&path, '/', 1);
		vect_add(&path, inp->data, ft_strlen(inp->data));
	}
	if (path.used == 0)
		vect_add(&path, inp->data, ft_strlen(inp->data));
	vect_mset_end(&path, '\0', 1);
	return (path.data);
}

int
	bi_cd
	(t_dict *env
	, t_lst *inp
	, int *ret)
{
	char	*path;

	(void)ret;
	path = cd_get_path(env, inp);
	if (path == NULL)
		return (0);
	if (chdir(path) == -1)
	{
		ERR("minishell: cd: %s: Permission denied", -1, path);
		free(path);
		return (-1);
	}
	free(path);
	return (1);
}
