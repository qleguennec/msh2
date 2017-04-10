/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:03:17 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/22 15:25:18 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ENOENV "minishell: env: %s not set"

int
	env_cpy_val
	(t_dict *env
	, char *key
	, t_vect *v)
{
	t_dict_ent	*ent;

	ent = dict_lookup(env, key);
	if (ent == NULL)
		return (FMTERR(ENOENV, 0, key));
	vect_add(v, ent->val.data, ent->val.used - 1);
	return (1);
}
